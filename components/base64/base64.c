#include "base64.h"


uint8_t base64_char_convert(uint8_t data) {
	if((data >= 0) && (data <= 25)) {
		return ('A' + data);
	}
	else if((data >= 26) && (data <= 51)) {
		return (data - 26) + 'a';
	}
	else if((data >= 52) && (data <= 61)) {
		return (data - 52) + '0';
	}
	else if(data == 62) {
		return '+';
	}
	else if(data == 63) {
		return '/';
	}
	else return '=';
}

uint16_t base64_encode(uint8_t *input_p, uint8_t *output_buf, uint16_t input_size) {
	for(uint16_t idx_input = 0; ; idx_input++) {
		if((idx_input * 3) < input_size) {
			output_buf[(idx_input * 4)] = base64_char_convert((input_p[idx_input * 3] >> 2) & 0x3F);
			output_buf[(idx_input * 4) + 1] = ((input_p[idx_input * 3] << 4) & 0x30);
		}
		else {
			return 0;
		}
		if(((idx_input * 3) + 1) < input_size) {
			output_buf[(idx_input * 4) + 1] = base64_char_convert(output_buf[(idx_input * 4) + 1] | ((input_p[idx_input * 3 + 1] >> 4) & 0x0F));
			output_buf[(idx_input * 4) + 2] = ((input_p[idx_input * 3 + 1] << 2) & 0x3C);
		}
		else {
			output_buf[(idx_input * 4) + 1] = base64_char_convert(output_buf[(idx_input * 4) + 1]);
			output_buf[(idx_input * 4) + 2] =  '=';
			output_buf[(idx_input * 4) + 3] =  '=';
			return (idx_input + 1) * 4;
		}
		
		if(((idx_input * 3) + 2) < input_size) {
			output_buf[(idx_input * 4) + 2] = base64_char_convert(output_buf[(idx_input * 4) + 2] | ((input_p[idx_input * 3 + 2] >> 6) & 0x03));
			output_buf[(idx_input * 4) + 3] = base64_char_convert(input_p[idx_input * 3 + 2] & 0x3F);
		}
		else {
			output_buf[(idx_input * 4) + 2] = base64_char_convert(output_buf[(idx_input * 4) + 2]);
			output_buf[(idx_input * 4) + 3] = '=';
			return (idx_input + 1) * 4;
		}
	}
	return 0;
}