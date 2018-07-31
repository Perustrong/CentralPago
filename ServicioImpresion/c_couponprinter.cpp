#include "ServicioImpresion/c_couponprinter.h"

c_CouponPrinter::c_CouponPrinter()
{
    cmd = new SSP_COMMAND();
    keys = new SSP_KEYS();
    sspKey = new SSP_FULL_KEY();
    info = new SSP_COMMAND_INFO();
    bool iniciado = false;

    // Create ssp library functions
    iniciado = InitialiseLibrary();

    cout << "Pasado por inicialización de libraria y resultado es = "<<iniciado<<endl;
    m_NumberOfChannels = 0;
    //m_Log = new CLogging();
    m_Type = 0;
    m_NumStackedNotes = 0;
    m_UnitData = 0;
    m_Response = new unsigned char[256];
    m_ResponseLength = 0;
}

c_CouponPrinter::~c_CouponPrinter()
{
 /*   if (m_UnitData)
        delete[] m_UnitData;
    delete[] m_Response;
//		delete m_Log;
    delete info;
    delete sspKey;
    delete keys;
    delete cmd;*/

}

// This method is used to load the library and link the function pointers defined
// in SSPInclude.h
bool c_CouponPrinter::InitialiseLibrary()
{
    // Load dll
    HINSTANCE hInst = LoadLibrary(TEXT("ITLSSPProc.dll"));
    cout <<"El hInst es = " << hInst<<endl;
    cout <<GetLastError()<<endl;
    printf("%x", hInst);
    if (hInst != NULL)
    {
        // Link function names

        // Open the COM port

        OpenPort = (LPFNDLLFUNC1)GetProcAddress(hInst, "OpenSSPComPortUSB");
        if (OpenPort == NULL)
        {
            FreeLibrary(hInst);
            return false;
        }

        // Close the COM port
        ClosePort = (LPFNDLLFUNC2)GetProcAddress(hInst, "CloseSSPComPortUSB");
        if (ClosePort == NULL)
        {
            FreeLibrary(hInst);
            return false;
        }

        // Send a command to the unit
        SSPSendCommand = (LPFNDLLFUNC3)GetProcAddress(hInst, "SSPSendCommand");
        if (SSPSendCommand == NULL)
        {
            FreeLibrary(hInst);
            return false;
        }

        // Create the generator and modulus prime numbers for the key encryption
        InitiateSSPHostKeys = (LPFNDLLFUNC4)GetProcAddress(hInst, "InitiateSSPHostKeys");
        if (InitiateSSPHostKeys == NULL)
        {
            FreeLibrary(hInst);
            return false;
        }

        // Create the final encryption key
        CreateSSPHostEncryptionKey = (LPFNDLLFUNC5)GetProcAddress(hInst, "CreateSSPHostEncryptionKey");
        if (CreateSSPHostEncryptionKey == NULL)
        {
            FreeLibrary(hInst);
            return false;
        }
    }
    else
        return false;
    return true;
}

// The enable command allows the validator to accept all commands.
bool c_CouponPrinter::EnablePrinter()
{
    cmd->CommandData[0] = SSP_CMD_ENABLE;
    cmd->CommandDataLength = 1;

    if (!SendCommand()) return false;

    // check response
    if (CheckGenericResponses())
        *m_Output << "Enabled validator" << endl;
    return true;
}

// Disable command stops the validator accepting most commands.
bool c_CouponPrinter::DisablePrinter()
{
    cmd->CommandData[0] = SSP_CMD_DISABLE;
    cmd->CommandDataLength = 1;

    if (!SendCommand()) return false;
    // check response
    if (CheckGenericResponses())
        *m_Output << "Disabled validator" << endl;
    return true;
}

// The reset command instructs the validator to restart (same effect as switching on and off)
bool c_CouponPrinter::ResetPrint()
{
    cmd->CommandData[0] = SSP_CMD_RESET;
    cmd->CommandDataLength = 1;
    if (!SendCommand()) return false;

    // check response
    if (CheckGenericResponses())
        *m_Output << "Resetting validator" << endl;
    return true;
}

// This function sets the protocol version in the validator to the version passed across. Whoever calls
// this needs to check the response to make sure the version is supported.
bool c_CouponPrinter::SetProtocolVersion(char pVersion)
{
    cmd->CommandData[0] = SSP_CMD_HOST_PROTOCOL_VERSION;
    cmd->CommandData[1] = pVersion;
    cmd->CommandDataLength = 2;
    if (!SendCommand()) return false;
    return true;
}

// This function sends the command LAST REJECT CODE which gives info about why a note has been rejected. It then
// outputs the info.


// This function performs a number of commands in order to setup the encryption between the host and the validator.
bool c_CouponPrinter::NegotiateKeys()
{
    int i;
    string s = "";

    // make sure encryption is off
    cmd->EncryptionStatus = false;

    // send sync
    cmd->CommandData[0] = SSP_CMD_SYNC;
    cmd->CommandDataLength = 1;

    if (!SendCommand()) return false;

    InitiateSSPHostKeys(keys, cmd);

    // send generator
    cmd->CommandData[0] = SSP_CMD_SET_GENERATOR;
    cmd->CommandDataLength = 9;
    for (i = 0; i < 8; ++i)
    {
        cmd->CommandData[i + 1] = (char)(keys->Generator >> (8 * i));
    }

    if (!SendCommand()) return false;

    // send modulus
    cmd->CommandData[0] = SSP_CMD_SET_MODULUS;
    cmd->CommandDataLength = 9;
    for (i = 0; i < 8; ++i)
    {
        cmd->CommandData[i + 1] = (char)(keys->Modulus >> (8 * i));
    }

    if (!SendCommand()) return false;

    // send key exchange
    cmd->CommandData[0] = SSP_CMD_KEY_EXCHANGE;
    cmd->CommandDataLength = 9;
    for (i = 0; i < 8; ++i)
    {
        cmd->CommandData[i + 1] = (char)(keys->HostInter >> (8 * i));
    }

    if (!SendCommand()) return false;

    keys->SlaveInterKey = 0;
    for (i = 0; i < 8; ++i)
    {
        keys->SlaveInterKey += (ULONG)cmd->ResponseData[1 + i] << (8 * i);
    }

    CreateSSPHostEncryptionKey(keys);

    // get full encryption key
    cmd->Key.FixedKey = 0x0123456701234567;
    cmd->Key.EncryptKey = keys->KeyHost;

    cmd->EncryptionStatus = true; // turn on encrypting

    *m_Output << "keys" << endl;
    return true;
}

// This function uses the setup request command to get information about the validator. The response
// packet is a variable length due to the fact that the number of channels is not known beforehand.
bool c_CouponPrinter::SetupRequest()
{
    // send setup request
    cmd->CommandData[0] = SSP_CMD_SETUP_REQUEST;
    cmd->CommandDataLength = 1;

    if (!SendCommand()) return false;

    // check response
    if (CheckGenericResponses())
    {
        // Output setup request data

        // Unit type
        *m_Output << "Unit type: ";
        m_Type = cmd->ResponseData[1];
        switch (m_Type)
        {
        case 0x00: *m_Output << "Note Validator" << endl; break;
        case 0x03: *m_Output << "SMART Hopper" << endl; break;
        case 0x06: *m_Output << "SMART Payout" << endl; break;
        case 0x07: *m_Output << "NV11" << endl; break;
        case 0x0B: *m_Output << "COUPON PRINTER" << endl; break;
        }

        // Firmware
        *m_Output << "Firmware: ";
        *m_Output << cmd->ResponseData[2] << cmd->ResponseData[3] << "." <<
            cmd->ResponseData[4] << cmd->ResponseData[5] << endl;

        // Channel setup
        // End of fixed data
        int index = 12;
        m_NumberOfChannels = cmd->ResponseData[index++];
        m_UnitData = new SChannelData[m_NumberOfChannels];

        index += m_NumberOfChannels; // Skip old channel values
        index += m_NumberOfChannels; // Skip channel security levels
        index += 3; // Skip value multiplier

        // Protocol version
        m_ProtocolVersion = cmd->ResponseData[index++];
        *m_Output << "Protocol Version: " << (int)m_ProtocolVersion << endl;

        // Setup channel data

        // Currencies
        *m_Output << "Channel Currencies: ";
        for (int i = 0; i < m_NumberOfChannels; ++i)
        {
            m_UnitData[i].Channel = i + 1;
            for (int j = 0; j < 3; ++j)
            {
                m_UnitData[i].Currency[j] = cmd->ResponseData[index + j];
                *m_Output << m_UnitData[i].Currency[j];
            }
            index += 3;
            *m_Output << " ";
        }
        *m_Output << endl;

        // Values
        *m_Output << "Channel Values: ";
        for (int i = 0; i < m_NumberOfChannels; ++i)
        {
            for (int j = 0; j < 4; ++j)
                m_UnitData[i].Value += (int)cmd->ResponseData[index++] << (8*j);
            *m_Output << m_UnitData[i].Value << " ";
        }
        *m_Output << endl;
    }
    return true;
}

// This function sends the set inhibits command to set the inhibits on the validator.
// The two bytes after the command byte represent two bit registers with each bit being
// a channel. 1-8 and 9-16 respectively. 0xFF = 11111111 in binary indicating all channels
// in this register are able to accept notes.


bool c_CouponPrinter::SyncPrinter()
{

    cmd->CommandData[0] = 0x11;

    //cmd->CommandData[2] = 0x00;

    cmd->CommandDataLength = 1;

    if (!SendCommand())
    {
        cout<< "Devuelto false 1a"<<endl;
        return false;
    }

    // If cmd fails on key not set, return false
    if (cmd->ResponseData[0] == 0xFA)
    {
        cout << "Devuelto false 1b"<<endl;
        return false;
    }

    CheckGenericResponses();

    // the command structure may be used halfway through the poll parse so copy the response
    // to a new array to prevent data being lost
    m_ResponseLength = cmd->ResponseDataLength;
    memcpy(m_Response, cmd->ResponseData, m_ResponseLength);

    //parse poll response
    cout << "Longidtuf recibida "<<m_ResponseLength<<endl;
    printf("%x",m_ResponseLength);
    for (int i = 0; i < m_ResponseLength; ++i)
    {
        switch (m_Response[i])
        {
        // The unit has been reset since the last time a poll was sent.
        case SSP_RESPONSE_CMD_OK:
            //*m_Output << "CMD OK" << endl;
            printf("Responde data %x",cmd->ResponseData[i]);
            cout<<endl;
            break;
        // If the byte after is greater than 0 then the note is being held in
        // escrow. If it is zero then the note is still being read.
        default:
            printf("Responde data %x",cmd->ResponseData[i]);
            cout<<endl;
            //*m_Output << "Recibido "<<m_Response[i]<<endl;
            break;
        }
    }

}


bool c_CouponPrinter::TicketPrint(unsigned char Index)
{

    cmd->CommandData[0] = 0x70;
    cmd->CommandData[1] = 0x02;
    cmd->CommandData[2] = Index;

    cmd->CommandDataLength = 3;

    bool Printed = false;

    cout<<"IMPRIMIENDO!!!"<<endl;

    if (!SendCommand())
    {
        cout<< "Devuelto false 1a"<<endl;
        return false;
    }

    // If cmd fails on key not set, return false
    if (cmd->ResponseData[0] == 0xFA)
    {
        cout << "Devuelto false 1b"<<endl;
        return false;
    }

    CheckGenericResponses();

    // the command structure may be used halfway through the poll parse so copy the response
    // to a new array to prevent data being lost
    m_ResponseLength = cmd->ResponseDataLength;
    memcpy(m_Response, cmd->ResponseData, m_ResponseLength);

    //parse poll response
    cout << "Longidtuf recibida "<<m_ResponseLength<<endl;
    printf("%x",m_ResponseLength);
    while (Printed == false)
    {
        CheckGenericResponses();
        m_ResponseLength = cmd->ResponseDataLength;
        memcpy(m_Response, cmd->ResponseData, m_ResponseLength);
        for (int i = 0; i < m_ResponseLength; ++i)
        {
            switch (m_Response[i])
            {
            // The unit has been reset since the last time a poll was sent.
            case SSP_RESPONSE_CMD_OK:
                //*m_Output << "CMD OK" << endl;
                printf("Responde data %x",cmd->ResponseData[i]);
                cout<<endl;
                break;
            case SSP_TICKET_PRINTED:
                cout << "Ticket Impreso"<<endl;
                return true;
            // If the byte after is greater than 0 then the note is being held in
            // escrow. If it is zero then the note is still being read.
            default:
                printf("Responde data %x",cmd->ResponseData[i]);
                cout<<endl;
                //*m_Output << "Recibido "<<m_Response[i]<<endl;
                break;
            }
        }
        DoPoll();
        Sleep(100);
    }
    return true;

}



// The poll function is called repeatedly to poll to validator for information, it returns as
// a response in the command structure what events are currently happening.
bool c_CouponPrinter::DoPoll()
{
    // send poll
    cmd->CommandData[0] = SSP_CMD_POLL;
    cmd->CommandDataLength = 1;

    if (!SendCommand()) return false;

    // If cmd fails on key not set, return false
    if (cmd->ResponseData[0] == 0xFA)
        return false;

  /*  CheckGenericResponses();

    // the command structure may be used halfway through the poll parse so copy the response
    // to a new array to prevent data being lost
    m_ResponseLength = cmd->ResponseDataLength;
    memcpy(m_Response, cmd->ResponseData, m_ResponseLength);

    //parse poll response
    int noteVal;
    string currency;
    for (int i = 1; i < m_ResponseLength; ++i)
    {
        switch (m_Response[i])
        {
            // The unit has been reset since the last time a poll was sent.
            case SSP_POLL_RESET:
                *m_Output << "Unit reset" << endl;
                break;
            // If the byte after is greater than 0 then the note is being held in
            // escrow. If it is zero then the note is still being read.
            case SSP_POLL_NOTE_READ:
                if (m_Response[i + 1] > 0)
                {
                    noteVal = GetChannelValue(m_Response[i + 1]);
                    currency = GetChannelCurrency(m_Response[i + 1]);
                    *m_Output << "Note in escrow, amount: ";
                    *m_Output << (float)noteVal << " " << currency[0] << currency[1]
                        << currency[2] << endl;
                }
                else
                    *m_Output << "Reading note" << endl;
                ++i;
                break;
            // The note has been accepted and credit given, the following byte will
            // contain the channel number of the credited note.
            case SSP_POLL_CREDIT:
                noteVal = GetChannelValue(m_Response[i + 1]);
                currency = GetChannelCurrency(m_Response[i + 1]);
                *m_Output << "Credit, amount: ";
                *m_Output << (float)noteVal << " " << currency[0] << currency[1]
                        << currency[2] << endl;
                ++m_NumStackedNotes;
                ++i;
                break;
            // Validator is in the process of rejecting a note.
            case SSP_POLL_REJECTING:
                break;
            // A note has been rejected from the validator.
            case SSP_POLL_REJECTED:
                *m_Output << "Note rejected" << endl;
                //QueryRejection(); // This will output info about the reason for the rejection
                break;
            // The validator is stacking a note.
            case SSP_POLL_STACKING:
                *m_Output << "Stacking note" << endl;
                break;
            // The validator has completed stacking a note.
            case SSP_POLL_STACKED:
                *m_Output << "Note stacked" << endl;
                break;
            // A note has become jammed in a place where it cannot be recovered.
            case SSP_POLL_SAFE_JAM:
                *m_Output << "Safe jam" << endl;
                break;
            // A note has become jammed in a place where it may possibly be recovered.
            case SSP_POLL_UNSAFE_JAM:
                *m_Output << "Unsafe jam" << endl;
                break;
            // The unit is disabled and will not accept notes.
            case SSP_POLL_DISABLED:
                *m_Output << "Unit disabled..." << endl;
                break;
            // The validator has detected a fraud attempt.
            case SSP_POLL_FRAUD_ATTEMPT:
                noteVal = GetChannelValue(m_Response[i + 1]);
                currency = GetChannelCurrency(m_Response[i + 1]);
                *m_Output << "Fraud attempt on ";
                *m_Output << (float)noteVal << " " << currency[0] << currency[1]
                        << currency[2] << endl;
                ++i;
                break;
            // The cashbox of the unit is full and cannot stack any more notes.
            case SSP_POLL_STACKER_FULL:
                *m_Output << "Stacker full" << endl;
                break;
            // A note has been rejected from the front of the validator on startup. This
            // may happen in the case of power loss while a note is reading.
            case SSP_POLL_NOTE_CLEARED_FROM_FRONT:
                noteVal = GetChannelValue(m_Response[i + 1]);
                currency = GetChannelCurrency(m_Response[i + 1]);
                *m_Output << "Note rejected on startup: ";
                *m_Output << (float)noteVal << " " << currency[0] << currency[1]
                        << currency[2] << endl;
                ++i;
                break;
            // A note has been stacked to the cashbox of the validator on startup. This
            // may happen in the case of power loss while a note is stacking.
            case SSP_POLL_NOTE_CLEARED_TO_CASHBOX:
                noteVal = GetChannelValue(m_Response[i + 1]);
                currency = GetChannelCurrency(m_Response[i + 1]);
                *m_Output << "Note stacked on startup: ";
                *m_Output << (float)noteVal << " " << currency[0] << currency[1]
                        << currency[2] << endl;
                ++i;
                break;
            // The cashbox of the unit has been removed.
            case SSP_POLL_CASHBOX_REMOVED:
                *m_Output << "Cashbox removed..." << endl;
                break;
            // The cashbox of the unit has been replaced.
            case SSP_POLL_CASHBOX_REPLACED:
                *m_Output << "Cashbox replaced" << endl;
                break;
            case SSP_POLL_BARCODE_TICKET_VALIDATED:
                *m_Output << "Barcode ticket validated" << endl;
                break;
            case SSP_POLL_BARCODE_TICKET_ACK:
                *m_Output << "Barcode ticket acknowledged" << endl;
                break;
            // The unit's top section has been opened (only applies to NV9/NV11 and NV200).
            // Protocol >= 6.
            case SSP_POLL_NOTE_PATH_OPEN:
                *m_Output << "Note path open" << endl;
                break;
            // This poll response indicates the unit is disabled as all the channels are
            // inhibited. Protocol >= 7.
            case SSP_POLL_CHANNEL_DISABLE:
                *m_Output << "Unit disabled (all channels inhibited)" << endl;
                break;
            // This poll response indicates the unit is initialising, it only appears when using
            // Poll with ACK (0x56).
            case SSP_POLL_INITIALISING:
                *m_Output << "Unit is initialising..." << endl;
                break;
            // If a poll response is detected and is not in this list
            default:
                *m_Output << "WARNING: Unrecognised poll response received - " << (int)m_Response[i]
                << endl;
                break;
        }
    }*/
    return true;
}

/* Non-Command functions */

// This function calls the open com port function of the SSP library and sets up
// the command structure.
bool c_CouponPrinter::OpenComPort(char portNum)
{
    if (OpenPort(cmd) == 0)
    {
        cout<<"Devuelto False";
        return false;
    }
    cout<<"Devuelto True";
    return true;
}

/* Exception and Error Handling */

// This is used for generic response error catching, it outputs the info in a
// meaningful way.
bool c_CouponPrinter::CheckGenericResponses()
{
   /* for(int i = 0; i<cmd->ResponseDataLength;i++)
    {
       // *m_Output << "Responde data " << cmd->ResponseData[i]<<endl;

        printf("Responde data %x",cmd->ResponseData[i]);
    }*/
    if (cmd->ResponseData[0] == SSP_RESPONSE_CMD_OK)
        return true;
    else
    {
        switch (cmd->ResponseData[0])
        {
            case SSP_RESPONSE_CMD_CANNOT_PROCESS:
                {
                    *m_Output << "Command response is CANNOT PROCESS COMMAND";
                    if (cmd->ResponseDataLength > 1)
                        *m_Output << ", error code - 0x" << cmd->ResponseData[1];
                    *m_Output << endl;
                    return false;
                }
            case SSP_RESPONSE_CMD_FAIL:
                {
                    *m_Output << "Command response is FAIL" << endl;
                    return false;
                }
            case SSP_RESPONSE_CMD_KEY_NOT_SET:
                {
                    *m_Output << "Command response is KEY NOT SET, renegotiate keys" << endl;
                    return false;
                }
            case SSP_RESPONSE_CMD_PARAM_OUT_OF_RANGE:
                {
                    *m_Output << "Command response is PARAM OUT OF RANGE" << endl;
                    return false;
                }
            case SSP_RESPONSE_CMD_SOFTWARE_ERROR:
                {
                    *m_Output << "Command response is SOFTWARE ERROR" << endl;
                    return false;
                }
            case SSP_RESPONSE_CMD_UNKNOWN:
                {
                    *m_Output << "Command response is UNKNOWN" << endl;
                    *m_Output << "Command response is UNKNOWN" << endl;
                    return false;
                }
            case SSP_RESPONSE_CMD_WRONG_PARAMS:
                {
                    *m_Output << "Command response is WRONG PARAMETERS" << endl;
                    return false;
                }
            default:
                return false;
        }
    }
}

bool c_CouponPrinter::AddLinePrinter(unsigned char PositionX[], unsigned char PositionY[], unsigned char Mensaje[],int SizeMensaje)
{



    cmd->CommandData[0] = 0x70;
    cmd->CommandData[1] = 0x01;
    cmd->CommandData[2] = 0x01;
    cmd->CommandData[3] = 0xfe;
    cmd->CommandData[4] = 0x01;
    cmd->CommandData[5] = 0x03;
    cmd->CommandData[6] = PositionX[0];
    cmd->CommandData[7] = PositionX[1];
    cmd->CommandData[8] = PositionY[0];
    cmd->CommandData[9] = PositionY[1];

    int InsertCero = 0;
    for(int i=0;i<SizeMensaje;i++)
    {

        cmd->CommandData[i+10+InsertCero] = Mensaje[i];
        cmd->CommandData[i+10+InsertCero+1] = 0x00;
        InsertCero=InsertCero+1;
    }


    cmd->CommandDataLength = (10+(SizeMensaje*2));

    if (!SendCommand())
    {
        cout<< "Devuelto false 1a"<<endl;
        return false;
    }

    // If cmd fails on key not set, return false
    if (cmd->ResponseData[0] == 0xFA)
    {
        cout << "Devuelto false 1b"<<endl;
        return false;
    }

    CheckGenericResponses();

    // the command structure may be used halfway through the poll parse so copy the response
    // to a new array to prevent data being lost
    m_ResponseLength = cmd->ResponseDataLength;
    memcpy(m_Response, cmd->ResponseData, m_ResponseLength);

    //parse poll response
    cout << "Longidtuf recibida "<<m_ResponseLength<<endl;
    printf("%x",m_ResponseLength);
    for (int i = 0; i < m_ResponseLength; ++i)
    {
        switch (m_Response[i])
        {
        // The unit has been reset since the last time a poll was sent.
        case SSP_RESPONSE_CMD_OK:
            //*m_Output << "CMD OK" << endl;
            printf("Responde data %x",cmd->ResponseData[i]);
            cout<<endl;
            break;
        // If the byte after is greater than 0 then the note is being held in
        // escrow. If it is zero then the note is still being read.
        default:
            printf("Responde data %x",cmd->ResponseData[i]);
            cout<<endl;
            //*m_Output << "Recibido "<<m_Response[i]<<endl;
            break;
        }
    }


}

bool c_CouponPrinter::AddImagePrinter(unsigned char PositionX[], unsigned char PositionY[], unsigned char Index)
{

    cmd->CommandData[0] = 0x70;
    cmd->CommandData[1] = 0x01;
    cmd->CommandData[2] = 0x05;
    cmd->CommandData[3] = 0xfe;
    cmd->CommandData[4] = Index;
    cmd->CommandData[5] = 0x00;
    cmd->CommandData[6] = PositionX[0];
    cmd->CommandData[7] = PositionX[1];
    cmd->CommandData[8] = PositionY[0];
    cmd->CommandData[9] = PositionY[1];




    cmd->CommandDataLength = (10);

    if (!SendCommand())
    {
        cout<< "Devuelto false 1a"<<endl;
        return false;
    }

    // If cmd fails on key not set, return false
    if (cmd->ResponseData[0] == 0xFA)
    {
        cout << "Devuelto false 1b"<<endl;
        return false;
    }

    CheckGenericResponses();

    // the command structure may be used halfway through the poll parse so copy the response
    // to a new array to prevent data being lost
    m_ResponseLength = cmd->ResponseDataLength;
    memcpy(m_Response, cmd->ResponseData, m_ResponseLength);

    //parse poll response
    cout << "Longidtuf recibida "<<m_ResponseLength<<endl;
    printf("%x",m_ResponseLength);
    for (int i = 0; i < m_ResponseLength; ++i)
    {
        switch (m_Response[i])
        {
        // The unit has been reset since the last time a poll was sent.
        case SSP_RESPONSE_CMD_OK:
            //*m_Output << "CMD OK" << endl;
            printf("Responde data %x",cmd->ResponseData[i]);
            cout<<endl;
            break;
        // If the byte after is greater than 0 then the note is being held in
        // escrow. If it is zero then the note is still being read.
        default:
            printf("Responde data %x",cmd->ResponseData[i]);
            cout<<endl;
            //*m_Output << "Recibido "<<m_Response[i]<<endl;
            break;
        }
    }

}

bool c_CouponPrinter::ClearTemplatePrinter(unsigned char Index)
{

    cmd->CommandData[0] = 0x70;
    cmd->CommandData[1] = 0x01;
    cmd->CommandData[2] = 0x06;
    cmd->CommandData[3] = 0xfe;

    cmd->CommandDataLength = (4);

    if (!SendCommand())
    {
        cout<< "Devuelto false 1a"<<endl;
        return false;
    }

    // If cmd fails on key not set, return false
    if (cmd->ResponseData[0] == 0xFA)
    {
        cout << "Devuelto false 1b"<<endl;
        return false;
    }

    CheckGenericResponses();

    // the command structure may be used halfway through the poll parse so copy the response
    // to a new array to prevent data being lost
    m_ResponseLength = cmd->ResponseDataLength;
    memcpy(m_Response, cmd->ResponseData, m_ResponseLength);

    //parse poll response
    cout << "Longidtuf recibida "<<m_ResponseLength<<endl;
    printf("%x",m_ResponseLength);
    for (int i = 0; i < m_ResponseLength; ++i)
    {
        switch (m_Response[i])
        {
        // The unit has been reset since the last time a poll was sent.
        case SSP_RESPONSE_CMD_OK:
            //*m_Output << "CMD OK" << endl;
            printf("Responde data %x",cmd->ResponseData[i]);
            cout<<endl;
            break;
        // If the byte after is greater than 0 then the note is being held in
        // escrow. If it is zero then the note is still being read.
        default:
            printf("Responde data %x",cmd->ResponseData[i]);
            cout<<endl;
            //*m_Output << "Recibido "<<m_Response[i]<<endl;
            break;
        }
    }

}

bool c_CouponPrinter::ClearFilePrinter(unsigned char Index)
{

    cmd->CommandData[0] = 0x71;
    cmd->CommandData[1] = 0x0A;
    cmd->CommandData[2] = 0x01;
    cmd->CommandData[3] = 0x01;
    cmd->CommandData[4] = Index;

    cmd->CommandDataLength = (5);

    if (!SendCommand())
    {
        cout<< "Devuelto false 1a"<<endl;
        return false;
    }

    // If cmd fails on key not set, return false
    if (cmd->ResponseData[0] == 0xFA)
    {
        cout << "Devuelto false 1b"<<endl;
        return false;
    }

    CheckGenericResponses();

    // the command structure may be used halfway through the poll parse so copy the response
    // to a new array to prevent data being lost
    m_ResponseLength = cmd->ResponseDataLength;
    memcpy(m_Response, cmd->ResponseData, m_ResponseLength);

    //parse poll response
    cout << "Longidtuf recibida "<<m_ResponseLength<<endl;
    printf("%x",m_ResponseLength);
    for (int i = 0; i < m_ResponseLength; ++i)
    {
        switch (m_Response[i])
        {
        // The unit has been reset since the last time a poll was sent.
        case SSP_RESPONSE_CMD_OK:
            //*m_Output << "CMD OK" << endl;
            printf("Responde data %x",cmd->ResponseData[i]);
            cout<<endl;
            break;
        // If the byte after is greater than 0 then the note is being held in
        // escrow. If it is zero then the note is still being read.
        default:
            printf("Responde data %x",cmd->ResponseData[i]);
            cout<<endl;
            //*m_Output << "Recibido "<<m_Response[i]<<endl;
            break;
        }
    }


}


// Takes a byte and converts it to a command name, returns a char string
char* c_CouponPrinter::GetCommandName(char commandByte)
{
    switch (commandByte)
    {
        case 0x4A: return "SET GENERATOR";
        case 0x4B: return "SET MODULUS";
        case 0x4C: return "REQUEST KEY EXCHANGE";
        case 0x01: return "RESET";
        case 0x02: return "SET INHIBITS";
        case 0x03: return "DISPLAY ON";
        case 0x04: return "DISPLAY OFF";
        case 0x05: return "SETUP REQUEST";
        case 0x06: return "HOST PROTOCOL VERSION";
        case 0x07: return "POLL";
        case 0x08: return "REJECT";
        case 0x09: return "DISABLE";
        case 0x0A: return "ENABLE";
        case 0x0B: return "PROGRAM FIRMWARE";
        case 0x0C: return "GET SERIAL NUMBER";
        case 0x0D: return "UNIT DATA";
        case 0x0E: return "CHANNEL VALUE DATA";
        case 0x0F: return "CHANNEL SECURITY DATA";
        case 0x10: return "CHANNEL RETEACH DATA";
        case 0x11: return "SYNC";
        case 0x12: return "UPDATE COIN ROUTE";
        case 0x13: return "DISPENSE";
        case 0x14: return "HOST SERIAL NUMBER REQUEST";
        case 0x15: return "SETUP REQUEST";
        case 0x17: return "LAST REJECT CODE";
        case 0x18: return "HOLD";
        case 0x19: return "ENABLE PROTOCOL VERSION EVENTS";
        case 0x23: return "GET BAR CODE READER CONFIGURATION";
        case 0x24: return "SET BAR CODE READER CONFIGURATION";
        case 0x25: return "GET BAR CODE INHIBIT";
        case 0x26: return "SET BAR CODE INHIBIT";
        case 0x27: return "GET BAR CODE DATA";
        case 0x54: return "CONFIGURE BEZEL";
        case 0x56: return "POLL WITH ACK";
        case 0x57: return "EVENT ACK";
        case 0x3B: return "SET ROUTING";
        case 0x3C: return "GET ROUTING";
        case 0x33: return "PAYOUT AMOUNT";
        case 0x35: return "GET NOTE/COIN AMOUNT";
        case 0x34: return "SET NOTE/COIN AMOUNT";
        case 0x38: return "HALT PAYOUT";
        case 0x3D: return "FLOAT AMOUNT";
        case 0x3E: return "GET MINIMUM PAYOUT";
        case 0x40: return "SET COIN MECH INHIBITS";
        case 0x46: return "PAYOUT BY DENOMINATION";
        case 0x44: return "FLOAT BY DENOMINATION";
        case 0x47: return "SET COMMAND CALIBRATION";
        case 0x48: return "RUN COMMAND CALIBRATION";
        case 0x3F: return "EMPTY ALL";
        case 0x50: return "SET OPTIONS";
        case 0x51: return "GET OPTIONS";
        case 0x49: return "COIN MECH GLOBAL INHIBIT";
        case 0x52: return "SMART EMPTY";
        case 0x53: return "CASHBOX PAYOUT OPERATION DATA";
        case 0x5C: return "ENABLE PAYOUT DEVICE";
        case 0x5B: return "DISABLE PAYOUT DEVICE";
        case 0x58: return "GET NOTE COUNTERS";
        case 0x59: return "RESET NOTE COUNTERS";
        case 0x30: return "SET REFILL MODE";
        case 0x41: return "GET NOTE POSITIONS";
        case 0x42: return "PAYOUT NOTE";
        case 0x43: return "STACK NOTE";
        case 0x45: return "SET VALUE REPORTING TYPE";
        case 0x70: return "TICKET PRINT";
        default: return "COMMAND NOT FOUND";
    }
}

bool c_CouponPrinter::SendCommand()
{
    // set the command name
    info->CommandName = (unsigned char*)GetCommandName(cmd->CommandData[0]);

    // attempt to send the command using the library
    if (SSPSendCommand(cmd, info) == 0)
    {
        // If the command fails
        ClosePort(); // close the com port
        *m_Output << "Failed to send command, port status: ";
        *m_Output << (int)cmd->ResponseStatus << endl;
//		m_Log->UpdateLog(info);
        return false;
    }
//	m_Log->UpdateLog(info);
    return true;
}

// This function sends a series of commands to the validator to initialise it for use.
// It opens the com port, negotiates keys for encryption, sets the protocol version,
// sets the inhibits and calls the setup request. After this function the validator is
// ready to be enabled and used.
bool c_CouponPrinter::ConnectToPrinter(const SSP_COMMAND& command, int protocolVersion, int attempts)
{
    // Set command structure data to the copy passed across
    // cmd is the internal command structure used by this class instance
    cmd->BaudRate = command.BaudRate;
    cmd->RetryLevel = command.RetryLevel;
    cmd->Timeout = command.Timeout;
    cmd->PortNumber = command.PortNumber;
    cmd->SSPAddress = command.SSPAddress;
    cmd->IgnoreError = command.IgnoreError;

    for (int i = 0; i < attempts; ++i)
    {
        // Close port in case it was left open
        //ClosePort();

        // Open the com port
        if (!OpenComPort(cmd->PortNumber))
        {
            *m_Output << "Failed to open port " << (int)cmd->PortNumber << endl;
            continue;
        }

        // Negotiate keys for encryption
        if (!NegotiateKeys())
        {
            *m_Output << "Failed on key negotiation..." << endl;
            continue;
        }


        // Set the protocol version to the value passed to this function
        if (!SetProtocolVersion(protocolVersion))
        {
            *m_Output << "Failed on setting protocol version..." << endl;
            continue;
        }

        // Set the inhibits (all uninhibited in this SDK)
        /*if (!SetInhibits())
        {
            *m_Output << "Failed on setting inhibits..." << endl;
            continue;
        }*/

        // Call setup request
        if (!SetupRequest())
        {
            *m_Output << "Failed on setup request..." << endl;
            continue;
        }
        return true;
    }
    return false;
}



