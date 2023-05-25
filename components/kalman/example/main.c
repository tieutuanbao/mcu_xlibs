#include "kalman.h"
#include <stdlib.h>

KalmanFilter_t filter;

void main() {
	KalmanFilter_init(&filter, 1, 1, 0.001);

    double val = KalmanFilter_updateEstimate(&filter, rand() % 1024);
    val = KalmanFilter_updateEstimate(&filter, rand() % 1024);
    val = KalmanFilter_updateEstimate(&filter, rand() % 1024);
    printf("Value filted after 3 sample from random: %lf", val)
}