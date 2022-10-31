/* Copyright (C) 2022 Nunuhara Cabbage <nunuhara@haniwa.technology>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, see <http://gnu.org/licenses/>.
 */

extern "C" {
#include "system4/cg.h"
}

#include <QObject>
#include <QImage>
#include <kio/thumbcreator.h>

class AliceThumbnailer : public ThumbCreator
{
public:
	AliceThumbnailer() = default;
	virtual ~AliceThumbnailer() = default;
	bool create(const QString &path, int w, int h, QImage &thumb) override;
	Flags flags() const override;
};

extern "C" {
	Q_DECL_EXPORT ThumbCreator *new_creator()
	{
		return new AliceThumbnailer();
	}
}

bool AliceThumbnailer::create(const QString &path, int w, int h, QImage &img)
{
	Q_UNUSED(w);
	Q_UNUSED(h);

	struct cg *cg = cg_load_file(path.toUtf8());
	if (!cg)
		return false;

	img = QImage((uchar*)cg->pixels, cg->metrics.w, cg->metrics.h,
			cg->metrics.w*4, QImage::Format_RGBA8888, free);
	// XXX: this is not the correct way to free a CG, but QImage needs to
	//      hold on to the pixel data
	free(cg);
	return true;
}

ThumbCreator::Flags AliceThumbnailer::flags() const
{
	return ThumbCreator::None;
}
