#ifndef C_COUPONPRINTER_H
#define C_COUPONPRINTER_H

#include "windows.h"
#include <string>
#include <iostream>
#include "ServicioImpresion/SSPInclude.h"
#include "ServicioImpresion/Commands.h"

using namespace std;


#define SSP_TICKET_PRINTED 0xa6


class c_CouponPrinter
{
    // ssp library variables
    SSP_COMMAND* cmd;
    SSP_KEYS* keys;
    SSP_FULL_KEY* sspKey;
    SSP_COMMAND_INFO* info;

    // Function pointers
    LPFNDLLFUNC1 OpenPort;
    LPFNDLLFUNC2 ClosePort;
    LPFNDLLFUNC3 SSPSendCommand;
    LPFNDLLFUNC4 InitiateSSPHostKeys;
    LPFNDLLFUNC5 CreateSSPHostEncryptionKey;

    // variable declarations
 //   CLogging* m_Log; // Logging class
    int m_NumStackedNotes; // Keep a track of the number of notes accepted by this unit
    SChannelData* m_UnitData; // The dataset data (channel num, value, currency)
    int m_NumberOfChannels; // The number of channels in this dataset
    unsigned char m_ProtocolVersion; // The protocol version the validator is using
    ostream* m_Output; // The output stream
    unsigned char m_Type; // The type of validator
    unsigned char* m_Response; // A backup of the poll response
    unsigned char m_ResponseLength; // The poll response length

public:



    c_CouponPrinter();
    ~c_CouponPrinter();


    // Inline Variable Access

    // access to ssp handles
    inline SSP_COMMAND* GetCommandStructure(){ return cmd; }
    inline SSP_COMMAND_INFO* GetInfoStructure(){ return info; }



    // get a channel value
    inline int GetChannelValue(int channelNum)
    {
        if (channelNum > 0 && channelNum <= m_NumberOfChannels)
        {
            for (int i = 0; i < m_NumberOfChannels; ++i)
            {
                if (m_UnitData[i].Channel == channelNum)
                    return m_UnitData[i].Value;
            }
        }
        return 0;
    }

    // get a channel currency
    inline char* GetChannelCurrency(int channelNum)
    {
        if (channelNum > 0 && channelNum <= m_NumberOfChannels)
        {
            for (int i = 0; i < m_NumberOfChannels; ++i)
            {
                if (m_UnitData[i].Channel == channelNum)
                    return m_UnitData[i].Currency;
            }
        }
        return 0;
    }

    // get the type of the unit
    inline unsigned char GetUnitType(){ return m_Type; }

    inline void SetOutputStream(ostream* o){ m_Output = o; m_Output->precision(2); *m_Output << fixed; }
    bool OpenComPort(char portNum);
    inline void CloseComPort(){ ClosePort(); }
    bool ConnectToPrinter(const SSP_COMMAND& command, int protocolVersion, int attempts);
    bool EnablePrinter();
    bool DisablePrinter();
    bool AddLinePrinter(unsigned char PositionX[], unsigned char PositionY[], unsigned char Mensaje[], int SizeMensaje);
    bool AddImagePrinter(unsigned char PositionX[], unsigned char PositionY[], unsigned char Index);
    bool ClearTemplatePrinter(unsigned char Index);
    bool ClearFilePrinter(unsigned char Index);
    bool ResetPrint();
    bool DoPoll();
    bool SyncPrinter();
    bool TicketPrint(unsigned char Index);



private:
    // Internal SSP lib functions
    bool InitialiseLibrary();
    // Internal Command Function definitions
    bool NegotiateKeys();
    bool SetupRequest();

    bool SetProtocolVersion(char pVersion);
    bool SendCommand();
    char* GetCommandName(char commandByte);
    bool CheckGenericResponses();




};

#endif // C_COUPONPRINTER_H



