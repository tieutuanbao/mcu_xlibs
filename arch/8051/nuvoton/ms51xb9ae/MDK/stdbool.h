#ifndef STDBOOL_H
#define STDBOOL_H

#if defined __C51__

#define bool uint8_t
#define false (0)
#define true (!false)

#endif

#endif
