/*  Template.cpp
 *
 *  Copyright (C) 2013  Jim Evins <evins@snaught.com>
 *
 *  This file is part of gLabels-qt.
 *
 *  gLabels-qt is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  gLabels-qt is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with gLabels-qt.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Template.h"


namespace libglabels
{

	Template::Template( const Template &other )
	{
		mBrand       = other.mBrand;
		mPart        = other.mPart;
		mDescription = other.mDescription;
		mPaperId     = other.mPaperId;
		mPageWidth   = other.mPageWidth;
		mPageHeight  = other.mPageHeight;
		mEquivPart   = other.mEquivPart;
		mName        = other.mName;
		mProductUrl  = other.mProductUrl;

		foreach ( Frame *frame, other.mFrames )
		{
			addFrame( frame );
		}

		foreach ( QString categoryId, other.mCategoryIds )
		{
			addCategory( categoryId );
		}
	}


	// Generic full page template
	Template *Template::full_page( const QString &paperId )
	{
		// TODO
		return NULL;
	}


	// From equivalent part number
	Template *Template::from_equiv( const QString &brand,
					const QString &part,
					const QString &equiv_part )
	{
		// TODO
		return NULL;
	}


	void Template::addCategory( const QString &categoryId )
	{
		mCategoryIds << categoryId;
	}


	void Template::addFrame( Frame *frame )
	{
		mFrames << frame;
	}


	bool Template::operator==( const Template &other ) const
	{
		return (mBrand == other.mBrand) && (mPart == other.mPart);
	}


	bool Template::hasCategory( const QString &categoryId ) const
	{
		foreach ( QString testCategoryId, mCategoryIds )
		{
			if ( categoryId == testCategoryId )
			{
				return true;
			}
		}

		return false;
	}


	bool Template::isSimilarTo( const Template &other ) const
	{
		// Does page size match?
		if ( (mPaperId    != other.mPaperId)    ||
		     (mPageWidth  != other.mPageWidth ) ||
		     (mPageHeight != other.mPageHeight ) )
		{
			return false;
		}

		// Are frames similar
		Frame *frame1 = mFrames.first();
		Frame *frame2 = other.mFrames.first();
		if ( !frame1->isSimilarTo( frame2 ) )
		{
			return false;
		}

		// Are they layed out similarly?
		foreach ( Layout *layout1, frame1->layouts() )
		{
			bool matchFound = false;
			foreach ( Layout *layout2, frame2->layouts() )
			{
				if ( layout1->isSimilarTo(layout2) )
				{
					matchFound = true;
					break;
				}
			}
			if ( !matchFound )
			{
				return false;
			}
		}

		return true;
	}


}

