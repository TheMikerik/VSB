
#include <mbed.h>
#include "i2c-lib.h"
#include "si4735-lib.h"

//************************************************************************

// Direction of I2C communication
#define R	0b00000001
#define W	0b00000000

#pragma GCC diagnostic ignored "-Wunused-but-set-variable"

DigitalOut g_led_PTA1( PTA1, 0 );
DigitalOut g_led_PTA2( PTA2, 0 );

DigitalIn g_but_PTC9( PTC9 );
DigitalIn g_but_PTC10( PTC10 );
DigitalIn g_but_PTC11( PTC11 );
DigitalIn g_but_PTC12( PTC12 );


///////////////////////////////////////////////////
uint8_t i2c_out_in( uint8_t t_adr, uint8_t *t_out_data, uint32_t t_out_len,uint8_t *t_in_data, uint32_t t_in_len ){
  i2c_start();

  uint8_t l_ack = i2c_output( t_adr | W );

  if ( l_ack == 0 ){
    for (int i = 0; i < t_out_len; i++ ) {
      l_ack |= i2c_output( t_out_data[ i ] ); // send all t_out_data
    }
  }
    //
  if ( l_ack != 0 ){ //eror ?
    i2c_stop();
    return l_ack;
  }
    //
  if ( t_in_data != nullptr ){
    i2c_start(); // repeated start

    l_ack |= i2c_output( t_adr | R );

    for (int i = 0; i < t_in_len; i++ ){
      i2c_ack();
      t_in_data[ i ] = i2c_input(); // receive all t_data_in
    }

    i2c_nack();
  }

  i2c_stop();

  return l_ack;
  }

////Vytvořte si třídu Expander s metodou void bar( uint8_t t_level );. Tato metoda zobrazí požadovaný počet (t_level) LED v řadě (sloupeček).

  class Expander{

  public:
	  Expander(){

	  }

	  void bar(uint8_t t_leve){
		  int led = 0;

		  for(uint8_t i = 0; i < t_leve; i ++){
			  led = (led << 1);
			  led += 1;
		  }
		  uint8_t data_out[4] = {led};
		  int l_ack = i2c_out_in(0x4E, data_out, 1, nullptr, 0);
	  }
  };


//Implementujte si třídu Radio s metodami set_volume( .. ),  search_freq( .. ),

  class Radio{

  public:
	  uint8_t set_volume(uint16_t sila){
		  if(sila > 63){
			  sila = 10;
		  }
		  uint8_t l_data_out[ 6 ] = { 0x12, 0x00, 0x40, 0x00, 0x00, sila };
		  return i2c_out_in( SI4735_ADDRESS, l_data_out, 6, nullptr, 0 );
	  }


	  uint8_t search_freq(){
		  uint8_t l_data_out[ 2 ] = { 0x21, 0b00001100};
		  return i2c_out_in( SI4735_ADDRESS, l_data_out, 2, nullptr, 0 );
	  }


	  uint8_t set_freq( uint16_t t_freq ) {
	    uint8_t l_data_out[ 5 ] = { 0x20, 0x00, t_freq >> 8, t_freq & 0xFF, 0 };
	    return i2c_out_in( SI4735_ADDRESS, l_data_out, 5, nullptr, 0 );
	  }

	  uint8_t get_tune_status( uint8_t *t_data_status, uint32_t t_data_len ) {
	    uint8_t l_data_out[ 2 ] = { 0x22, 0 };
	    return i2c_out_in( SI4735_ADDRESS, l_data_out, 2, t_data_status, t_data_len );
	  }
  };

//////////////////////////////////////////////////

int main( void ){
	//uint8_t l_S1, l_S2, l_RSSI, l_SNR, l_MULT, l_CAP;
	//uint8_t l_ack = 0;

	Radio rad;
	int l_ack;

	i2c_init();

	if( (l_ack = si4735_init() != 0)){
		printf("Initialization of SI4735 finish with error (%d)\r\n", l_ack);
		return 0;
	}
	else{
		printf("SI4735 initialized.\r!n");
	}

	l_ack = rad.set_freq(8900);
	l_ack = rad.set_volume(30);

	if(!l_ack){
		printf("Ne");
	}

	Expander led;
	led.bar(4);


	while(1);
	return 0;
}

