#include "BayesFilters/PFCorrection.h"

using namespace bfl;
using namespace Eigen;


PFCorrection::PFCorrection() noexcept { };


PFCorrection::PFCorrection(PFCorrection&& pf_prediction) noexcept :
    skip_(pf_prediction.skip_)
{
    pf_prediction.skip_ = false;
}


void PFCorrection::correct(const Ref<const MatrixXf>& pred_states, const Ref<const VectorXf>& pred_weights, const Ref<const MatrixXf>& measurements,
                           Ref<MatrixXf> cor_states, Ref<VectorXf> cor_weights)
{
    if (!skip_)
        correctStep(pred_states, pred_weights, measurements,
                    cor_states, cor_weights);
    else
    {
        cor_states  = pred_states;
        cor_weights = pred_weights;
    }
}


bool PFCorrection::skip(const bool status)
{
    skip_ = status;

    return true;
}
