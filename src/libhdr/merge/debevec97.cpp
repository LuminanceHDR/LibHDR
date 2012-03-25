/*
 * This file is a part of LibHDR package.
 * ----------------------------------------------------------------------
 * Copyright (C) 2012 Davide Anastasia
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 * ----------------------------------------------------------------------
 */

#include "debevec97.h"

#include <boost/shared_ptr.hpp>
#include <iostream>
#include <limits>

namespace LibHDR
{
namespace Merge
{
namespace
{
// Base class for Response
struct Response
{
    Response() {}
    virtual ~Response() {}

    virtual float response(float value) = 0;
};

// Linear response class
struct ResponseLinear : public Response
{
    float response(float value)
    {
        return value;
    }
};

// Base class for Weights
struct Weights
{
    Weights() {}
    virtual ~Weights() {}

    virtual float weight(float value) = 0;

    virtual float getMinimunTrustWeight() = 0;
    virtual float getMaximumTrustWeight() = 0;
};

namespace
{
const float minTrustWeightTriangular = 2.f/255.f;
const float maxTrustWeightTriangular = 254.f/255.f;
const float middlePointTrustArea = minTrustWeightTriangular + (maxTrustWeightTriangular - minTrustWeightTriangular)/2.f;
const float triangularWeightsSlope = 2.f/(maxTrustWeightTriangular - minTrustWeightTriangular);
}

// Triangular weights class
struct WeightsTriangular : public Weights
{
    WeightsTriangular()
    {
        using std::cout;
        using std::endl;

        cout << "WeightsTriangular {min: " <<minTrustWeightTriangular << ", ";
        cout << "max: " << maxTrustWeightTriangular << ", ";
        cout << "middle: " << middlePointTrustArea << ", ";
        cout << "slope: " << triangularWeightsSlope << "}" << endl;
    }


    float weight(float value)
    {
        if (value < minTrustWeightTriangular) return 0.0f;
        if (value > maxTrustWeightTriangular) return 0.0f;

        if ( value > middlePointTrustArea )
        {
            return -triangularWeightsSlope*(value - maxTrustWeightTriangular);
        }
        else
        {
            return triangularWeightsSlope*(value - minTrustWeightTriangular);
        }
    }

    float getMinimunTrustWeight()
    {
        return minTrustWeightTriangular + std::numeric_limits<float>::epsilon();
    }
    virtual float getMaximumTrustWeight()
    {
        return maxTrustWeightTriangular - std::numeric_limits<float>::epsilon();
    }
};

}

// This class is the private implementation of the Debevec97 class
// It holds shared pointer to a Response class (on of its subclasses)
// and the Weights class (one of its subclasses)
struct Debevec97Impl
{
    Debevec97Impl():
        response_(new ResponseLinear),
        weights_(new WeightsTriangular)
    {}

    void setWeightsType()
    {}
    void setResponseType()
    {}

    float getWeight(float value)
    {
        return weights_->weight(value);
    }

    float getResponse(float value)
    {
        return response_->response(value);
    }

//private:
    boost::shared_ptr<Response> response_;
    boost::shared_ptr<Weights> weights_;
};

Debevec97::Debevec97():
    m_impl(new Debevec97Impl)
{}

Debevec97::~Debevec97()
{}

// Ideally at this stage, I have in image an Image ready to be filled, and in images
// a right set of images
void Debevec97::coreMerge(ImagePtr image, const std::vector<ImagePtr>& images, const Settings& /*settings*/)
{
    const float maxTrustWeight = m_impl->weights_->getMaximumTrustWeight();
    const float minTrustWeight = m_impl->weights_->getMinimunTrustWeight();

    // set initial pointers
    Pixel* output_pixel = image->data();

    for (int row = 0; row < image->getRows(); ++row)
    {
        for (int col = 0; col < image->getCols(); ++col)
        {
            float sumR = 0.0f;
            float sumG = 0.0f;
            float sumB = 0.0f;

            float divR = 0.0f;
            float divG = 0.0f;
            float divB = 0.0f;

            float maxti = -std::numeric_limits<float>::max();
            float minti = std::numeric_limits<float>::max();

            float index_for_whiteR = 1.f;
            float index_for_whiteG = 1.f;
            float index_for_whiteB = 1.f;

            float index_for_blackR = 0.f;
            float index_for_blackG = 0.f;
            float index_for_blackB = 0.f;

            for (size_t i = 0; i < images.size(); ++i)
            {
                const Pixel& current_image = *(images[i]->constData() + (row*image->getCols()) + col);

                float red = current_image.f32[0];
                float green = current_image.f32[1];
                float blue = current_image.f32[2];

                float ti = images[i]->exifData().getAverageSceneLuminance();   // is it right?

                // if at least one of the color channel's values are in the bright "not-trusted zone"
                // and we have min exposure time
                if ( (red > maxTrustWeight || green > maxTrustWeight || blue > maxTrustWeight) && (ti < minti) )
                {
                    //update the indexes_for_whiteRGB, minti
                    index_for_whiteR = red;
                    index_for_whiteG = green;
                    index_for_whiteB = blue;
                    minti = ti;
                }

                // if at least one of the color channel's values are in the dim "not-trusted zone"
                // and we have max exposure time
                if ( (red < minTrustWeight || green < minTrustWeight || blue < minTrustWeight) && (ti > maxti) )
                {
                    //update the indexes_for_blackRGB, maxti
                    index_for_blackR = red;
                    index_for_blackG = green;
                    index_for_blackB = blue;
                    maxti = ti;
                }

                float w_average = (m_impl->getWeight(red) +
                                   m_impl->getWeight(green) +
                                   m_impl->getWeight(blue))/3.0f;

                sumR += w_average * m_impl->getResponse(red) / ti;
                divR += w_average;
                sumG += w_average * m_impl->getResponse(green) / ti;
                divG += w_average;
                sumB += w_average * m_impl->getResponse(blue) / ti;
                divB += w_average;
            }

            if ( divR == 0.0f || divG == 0.0f || divB == 0.0f )
            {
                if (maxti > -1e6f)
                {
                    sumR = m_impl->getResponse(index_for_blackR) / maxti;
                    sumG = m_impl->getResponse(index_for_blackG) / maxti;
                    sumB = m_impl->getResponse(index_for_blackB) / maxti;
                    divR = divG = divB = 1.0f;
                }
                if (minti < +1e6f)
                {
                    sumR = m_impl->getResponse(index_for_whiteR) / minti;
                    sumG = m_impl->getResponse(index_for_whiteG) / minti;
                    sumB = m_impl->getResponse(index_for_whiteB) / minti;
                    divR = divG = divB = 1.0f;
                }
            }

            // set final pixel
            (*output_pixel).f32[0] = sumR/divR;
            (*output_pixel).f32[1] = sumG/divG;
            (*output_pixel).f32[2] = sumB/divB;
            (*output_pixel).f32[3] = 1.f;

            output_pixel++; // next pixel!
        }
    }
}

std::string getID()
{
    return std::string("debevec97");
}

}
}
