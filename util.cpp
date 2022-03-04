#include <Arduino.h>
#include "util.h"

void serial_bprintf(char *buf, const char *fmt, ...) {
	va_list argp;
	va_start(argp, fmt);
	vsprintf(buf, fmt, argp);
	Serial.print(buf);
	va_end(argp);
}

void serial_sbprintf(HardwareSerial *serial, char *buf, const char *fmt, ...) {
	va_list argp;
	va_start(argp, fmt);
	vsprintf(buf, fmt, argp);
	serial->print(buf);
	va_end(argp);
}

void serial_printf(const char *fmt, ...) {
	char buf[128];
	va_list argp;
	va_start(argp, fmt);
	vsprintf(buf, fmt, argp);
	Serial.print(buf);
	va_end(argp);
}

char* ltrim(char *buf) {
	char *p, *p2;

	for(p = buf;(*p == '\r' || *p == '\n') && *p != '\0'; p++);

	for(p2 = p;*p2 != '\0'; p2++) {
		buf[p2-p] = *p2;
	}

	buf[p2-p] = '\0';
	return buf;
}

char *rtrim(char *buf) {
	char *p = buf+strlen(buf);

	for(;p >= buf && (*p == '\r' || *p == '\n' || *p == '\0'); p--);

	if((*(p+1) == '\r' || *(p+1) == '\n'))
		*(p+1) = '\0';
	return buf;
}


#ifdef __arm__
// should use uinstd.h to define sbrk but Due causes a conflict
extern "C" char* sbrk(int incr);
#else  // __ARM__
extern char *__brkval;
#endif  // __arm__

int freeMemory() {
	char top;
#ifdef __arm__
  return &top - reinterpret_cast<char*>(sbrk(0));
#elif defined(CORE_TEENSY) || (ARDUINO > 103 && ARDUINO != 151)
	return &top - __brkval;
#else  // __arm__
  return __brkval ? &top - __brkval : &top - __malloc_heap_start;
#endif  // __arm__
}
