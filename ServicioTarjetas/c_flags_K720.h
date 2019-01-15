#ifndef C_FLAGS_K720_H
#define C_FLAGS_K720_H
#include<windows.h>


class c_flags_K720
{
	public:
		
		c_flags_K720();
		
		~c_flags_K720();
		
		bool* leer_com();
		bool* estado_com();
		bool* escribir_com();
		bool* sensor1_com();
                bool* sensor2_com();
                bool* sensor3_com();
		void flag_lectura_com(bool flag);
		void flag_status_com(bool flag);
		void flag_escritura_com(bool flag);
                void flag_sensor1_com(bool flag);
                void flag_sensor2_com(bool flag);
                void flag_sensor3_com(bool flag);

		
	protected:
		
	private:
		
		bool lectura_com;
		bool escritura_com;
		bool status_com;
		bool sensor1=false;
        bool sensor2=false;
        bool sensor3=false;
};

#endif
