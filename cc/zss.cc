#include "zss.h"

enum {
    ZSS_MODE_RAW, ZSS_MODE_NUM
};

static const unsigned char masks[10] = {    //
    0x3f, 0x06, 0x5b, 0x4f, 0x66, 0x6d, 0x7d, 0x07, 0x7f, 0x6f    //
    };

void zss::set_num(int num)
{
    _mode = ZSS_MODE_NUM;
    _num = num;
}

void zss::update(void)
{
    static int curr_digit = 0;
    int i, j;
    static int num;

    for(i = 0; i < _digits; i++)
        set_digit_f(i, 1);    // shut down all digits

    switch(_mode) {
        case ZSS_MODE_NUM:
            if(curr_digit == 0)
                num = _num;
            else
                num /= 10;

            for(j = 0; j < _segments; j++) {
                if(masks[num % 10] & (1 << j))
                    set_segment_f(j, 1);
                else
                    set_segment_f(j, 0);
            }
            if(curr_digit == _dot_pos)
                set_segment_f(7, 1);
            else
                set_segment_f(7, 0);
            set_digit_f(_digits - curr_digit - 1, 0);    // reversed
            break;
        case ZSS_MODE_RAW:
            for(j = 0; j < _segments; j++) {
                if(_raw[curr_digit] & (1 << j))
                    set_segment_f(j, 1);
                else
                    set_segment_f(j, 0);
            }
            set_digit_f(curr_digit, 0);
            break;
    }
    curr_digit++;
    curr_digit %= _digits;
}

void zss::set_dot(int pos)
{
    _dot_pos = pos;
}

void zss::set_raw(unsigned char* raw)
{
    _raw = raw;
    _mode = ZSS_MODE_RAW;
}
