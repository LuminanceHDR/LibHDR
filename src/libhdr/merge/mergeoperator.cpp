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

#include "mergeoperator.h"

#include <vector>
#include <iostream>
#include <boost/lambda/lambda.hpp>

using namespace std;

namespace LibHDR
{
namespace Merge
{
MergeOperator::MergeOperator()
{}

MergeOperator::~MergeOperator()
{}

namespace
{
class SizeCheck
{
public:
    SizeCheck(int width, int height):
        width_(width),
        height_(height),
        check_(true)
    {}

    void operator()(const ImagePtr& img)
    {
        if (img->getWidth() != width_) check_ = false;
        if (img->getHeight() != height_) check_ = false;
    }

    int width_;
    int height_;
    bool check_;
};

//! \brief returns an empty \c Image based on the size of the input images
//! \throw MismatchImagesException
ImagePtr getEmptyImage(const std::vector<ImagePtr>& images)
{
    cerr << "getEmptyImage()" << endl;

    SizeCheck sz(images[0]->getWidth(), images[0]->getHeight());

    sz = for_each(images.begin(), images.end(), sz);

    if ( sz.check_ )
        return ImagePtr(new Image(sz.width_, sz.height_));
    else
        throw MismatchImagesException("MismatchImagesException: pictures don't have the same size");
}

void checkImagesExposureValue(const std::vector<ImagePtr>& images)
{
    std::vector<ImagePtr>::const_iterator it = images.begin();
    while (it != images.end())
    {
        if ( (*it)->exifData().isValid() == false )
            throw std::runtime_error("Empty EXIF data");

        ++it;
    }
}

}

ImagePtr MergeOperator::merge(const std::vector<ImagePtr>& images, const Settings& settings)
{
    if (images.size() == 0) throw NoImagesException("NoImagesException: no picture supplied to the merge operator");

    checkImagesExposureValue(images);

    ImagePtr image = getEmptyImage(images);

    coreMerge(image, images, settings);

    return image;
}

}
}

