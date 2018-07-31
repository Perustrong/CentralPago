#ifndef C_FLAGS_NV9_H
#define C_FLAGS_NV9_H
#include <windows.h>
#include <iostream>
#include <unistd.h>
#include <stdio.h>
#include <stdint.h>

class c_flags_NV9
{
public:

        c_flags_NV9();

       // ~c_flags();

        bool* leer_com();
        bool* estado_com();
        bool* escribir_com();
        unsigned char SyncBill_com();
        void flag_lectura_com(bool flag);
        void flag_status_com(bool flag);
        void flag_escritura_com(bool flag);
        void flag_sincronismo_com(unsigned char flag);

    protected:

    private:

        bool lectura_com = false;
        bool escritura_com = false;
        bool status_com = false;
        unsigned char sincronismo_bill_com = 0x00;
};

#endif // C_FLAGS_NV9_H
