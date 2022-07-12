#ifndef __ALGORITHM_H
#define __ALGORITHM_H

#include <stdint.h>


#define DC_REMOVAL_ALPHA 0.95
#define MEAN_FILTER_SIZE 15


typedef struct {
  float w;
  float result;
} dc_filter_t;

typedef struct {
  float values[MEAN_FILTER_SIZE];
  uint8_t index;
  float sum;
  uint8_t count;
} mean_diff_filter_t;

typedef struct {
  float v[2];
  float result;
} butter_worth_filter_t;

dc_filter_t max30102_alg_dc_removal(float x, float prev_w, float alpha);
float max30102_alg_meanDiff(float M, mean_diff_filter_t* filterValues);
void max30102_alg_low_pass_butterworth_filter(float x, butter_worth_filter_t * filterResult);


#endif
