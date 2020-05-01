uint8_t tx_spi_byte(uint8_t outgoing)
{
	uint8_t i, incoming;
	incoming = 0;

	//Send outgoing byte
	for(i = 0 ; i < 8 ; i++)
	{
		if(outgoing & 0b10000000)
		sbi(PORTA, TX_MOSI);
		else
		cbi(PORTA, TX_MOSI);
		
		sbi(PORTA, TX_SCK); //TX_SCK = 1;

		//MISO bit is valid after clock goes going high
		incoming <<= 1;
		if( PINA & (1<<TX_MISO) ) incoming |= 0x01;

		cbi(PORTA, TX_SCK); //TX_SCK = 0;
		
		outgoing <<= 1;
	}

	return(incoming);
}
