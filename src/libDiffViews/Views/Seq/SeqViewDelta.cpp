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

#include <QTextStream>
#include <QPainter>

#include "SequentialView.hpp"
#include "SeqViewDelta.hpp"

namespace DiffViews
{

    SeqViewDeltaHeader::SeqViewDeltaHeader( SeqViewInfo* info, FilePatch::Ptr patch )
        : SeqViewItem( info )
    {
        QString strRaw;
        QTextStream rawStream( &strRaw );
        patch->FilePatch::exportRaw( rawStream );
        mTextLines = strRaw.split( QChar( L'\n' ), QString::SkipEmptyParts );
    }

    qreal SeqViewDeltaHeader::setWidth( qreal width )
    {
        QFontMetricsF fm( info()->mFixed );
        qreal height = qRound( fm.lineSpacing() ) * mTextLines.count();
        SeqViewItem::setWidth( width, height );
        return height;
    }

    void SeqViewDeltaHeader::paint( QPainter* p, const QStyleOptionGraphicsItem*, QWidget* )
    {
        SeqViewInfo* i = info();

        QFontMetricsF fm( i->mFixed );
        QLinearGradient grad( 0., 0., 0., height() );

        grad.setColorAt( 0., i->clrDeltaFirst );
        grad.setColorAt( 1., i->clrDeltaSecond );
        p->setBrush( grad );
        p->setPen( i->clrSeparator );
        p->drawRect( 10, 0, width() - 20, height() );

        p->setPen( i->clrText );
        p->setFont( i->mFixed );
        int top = 0;
        foreach( QString line, mTextLines )
        {
            p->drawText( QRectF( 12, top, width() - 24, fm.lineSpacing() ),
                         Qt::AlignLeft | Qt::AlignVCenter | Qt::TextWrapAnywhere,
                         line );
            top += qRound( fm.lineSpacing() );
        }
    }

}
