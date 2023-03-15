#ifndef _ZSS_H
#define _ZSS_H

class zss {
public:
    void update(void);
    void bind(
        void (*set_segment)(unsigned int segment, int state),
        void (*set_digit)(unsigned int digit, int state)
            )
    {
        set_segment_f = set_segment;
        set_digit_f = set_digit;
    }

    void set_num(int num);
    void set_dot(int pos);
    void set_raw(unsigned char* raw);

private:
    int _digits, _segments;

    int _num;
    unsigned char _mode, _dot_pos;
    unsigned char* _raw;

    // cbs
    void (*set_segment_f)(unsigned int segment, int state);
    void (*set_digit_f)(unsigned int digit, int state);
};

#endif
