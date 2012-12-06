/*
 * MacGitver
 * Copyright (C) 2012 Sascha Cunz <sascha@babbelbox.org>
 *
 * This program is free software; you can redistribute it and/or modify it under the terms of the
 * GNU General Public License (Version 2) as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
 * even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License along with this program; if
 * not, see <http://www.gnu.org/licenses/>.
 *
 */

#include <QTextBrowser>
#include <QVBoxLayout>

#include "Views/Interfaces/DiffViews.hpp"
#include "Views/Raw/RawHighlighter.hpp"
#include "Views/Raw/RawView.hpp"

namespace DiffViews
{

    RawView::RawView( QWidget* parent )
        : DiffView( parent )
    {
        mBrowser = new QTextBrowser;
        mBrowser->setFrameShape( QFrame::NoFrame );

        QVBoxLayout* l = new QVBoxLayout;
        l->setMargin( 0 );
        l->setSpacing( 0 );
        l->addWidget( mBrowser );
        setLayout( l );

        new RawHighlighter( mBrowser );

    //  setFont( Config::defaultFixedFont() );

    }

    RawView::~RawView()
    {
    }

    void RawView::setPatch( Patch::Ptr patch )
    {
        QString patchText;

        mCurrentPatch = patch;

        if( patch )
        {
            patchText = patch->toString();
        }

        mBrowser->setText( patchText );
    }

    MGVDV_IMPLEMENT_DIFFVIEWCREATOR(RawView)

}