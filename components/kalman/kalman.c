#include "kalman.h"

void KalmanFilter_init(KalmanFilter_t *filter,double mea_e, double est_e, double q)
{
  filter->errMeasure = mea_e;
  filter->errEstimate = est_e;
  filter->QParam = q;
}

double KalmanFilter_getKalmanGain(KalmanFilter_t *filter) {
  return filter->kalmanGain;
}

double KalmanFilter_getEstimateError(KalmanFilter_t *filter) {
  return filter->errEstimate;
}

void KalmanFilter_setMeasurementError(KalmanFilter_t *filter, double mea_e)
{
  filter->errMeasure=mea_e;
}

void KalmanFilter_setEstimateError(KalmanFilter_t *filter, double est_e)
{
  filter->errEstimate=est_e;
}

void KalmanFilter_setProcessNoise(KalmanFilter_t *filter, double q)
{
  filter->QParam=q;
}

double KalmanFilter_updateEstimate(KalmanFilter_t *filter, double mea)
{
  filter->kalmanGain = filter->errEstimate/(filter->errEstimate + filter->errMeasure);
  filter->currentEstimate = filter->lastEstimate + filter->kalmanGain * (mea - filter->lastEstimate);
  filter->errEstimate =  (1.0 - filter->kalmanGain)*filter->errEstimate + fabs(filter->lastEstimate-filter->currentEstimate)*filter->QParam;
  filter->lastEstimate=filter->currentEstimate;

  return filter->currentEstimate;
}
