/*
 * adc.h
 *
 * Created: 14/04/2019 13:49:44
 *  Author: Matthijs Padding
 */


#ifndef ADC_H_
#define ADC_H_

namespace Converter {
	void init() {
		ADMUX = (1<<REFS0)|(1<<ADLAR);
		ADCSRA = (1<<ADEN)|(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0);
	}

	/* Returns result of ADC on previous read channel */
	uint16_t read() {
		/* Start conversion */
		ADCSRA |= (1<<ADSC);
		
		/* wait till conversion is complete */
		while(ADCSRA & (1<<ADSC));
		
		/* Return result */
		return (ADC);
	}
	
	/* Returns result of ADC on specified channel */
	uint16_t read(uint8_t channel) {
		/* Map to 0-7 */
		channel &= 0x7;
			
		/* Clear bottom 3 bits before ORing with channel */
		ADMUX = (ADMUX & 0xF8) | channel;
			
		return read();
	}

	uint8_t low_read() {
		/* Start conversion */
		ADCSRA |= (1<<ADSC);
		
		/* wait till conversion is complete */
		while(ADCSRA & (1<<ADSC));
		
		return ADCH;
	}

	uint8_t low_read(uint8_t channel) {
		channel &= 0x7;
		
		ADMUX = (ADMUX & 0xF8) | channel;
		
		return low_read();
	}
}

#endif /* ADC_H_ */
