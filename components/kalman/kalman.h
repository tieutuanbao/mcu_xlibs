#ifndef __KALMAN_FILTER_H__
#define __KALMAN_FILTER_H__

#include <stdlib.h>

typedef struct{
	double errMeasure;
	double errEstimate;
	double QParam;
	double currentEstimate;
	double lastEstimate;
	double kalmanGain;
} KalmanFilter_t;

void KalmanFilter_init(KalmanFilter_t *filter,double mea_e, double est_e, double q);
double KalmanFilter_updateEstimate(KalmanFilter_t *filter,double mea);
void KalmanFilter_setMeasurementError(KalmanFilter_t *filter,double mea_e);
void KalmanFilter_setEstimateError(KalmanFilter_t *filter,double est_e);
void KalmanFilter_setProcessNoise(KalmanFilter_t *filter,double q);
double KalmanFilter_getKalmanGain(KalmanFilter_t *filter);
double KalmanFilter_getEstimateError(KalmanFilter_t *filter);

#endif
