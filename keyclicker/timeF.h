#ifndef TIME_H
#define TIME_H

typedef enum {OFF, LOW, MEDIUM, HIGH} OL;
extern OL offsetLevel;

extern bool timeToggle;
extern bool filled;

int set_Seconds(int seconds, int digits[]);
int calc_Offset(OL offsetLevel, int seconds);
void set_Countdown(int countdown, int digits[]);
bool time_Button(void);
void offset_Select(void);

#endif
