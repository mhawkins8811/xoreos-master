/* xoreos - A reimplementation of BioWare's Aurora engine
 *
 * xoreos is the legal property of its developers, whose names
 * can be found in the AUTHORS file distributed with this source
 * distribution.
 *
 * xoreos is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 *
 * xoreos is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with xoreos. If not, see <http://www.gnu.org/licenses/>.
 */

/** @file
 *  A creature in a Dragon Age: Origins area.
 */

#ifndef ENGINES_DRAGONAGE_CREATURE_H
#define ENGINES_DRAGONAGE_CREATURE_H

#include <vector>
#include <list>

#include "src/common/ptrlist.h"
#include "src/common/ustring.h"

#include "src/aurora/types.h"

#include "src/graphics/aurora/types.h"

#include "src/engines/dragonage/types.h"
#include "src/engines/dragonage/object.h"

namespace Aurora {
	class GDAFile;
}

namespace Engines {

namespace DragonAge {

class Creature : public Object {
public:
	/** Create a dummy creature instance. Not playable as it is.*/
	Creature();
	/** Load from a placeable instance. */
	Creature(const Aurora::GFF3Struct &placeable);
	~Creature();

	/** Create a fake player character creature for testing purposes. */
	void createFakePC();

	// Basic visuals

	void show(); ///< Show the creature's model.
	void hide(); ///< Hide the creature's model.

	// Basic properties

	bool isPC() const; ///< Is the creature a player character?

	// Object/Cursor interactions

	void enter(); ///< The cursor entered the creature.
	void leave(); ///< The cursor left the creature.

	/** (Un)Highlight the creature. */
	void highlight(bool enabled);

	/** The creature was clicked. */
	bool click(Object *triggerer = 0);

	// Positioning

	/** Set the creature's position. */
	void setPosition(float x, float y, float z);
	/** Set the creature's orientation. */
	void setOrientation(float x, float y, float z, float angle);


private:
	/** Max number of model parts for a creature's head. */
	static const size_t kPartVariationCount = 4;

	/** An item equipped by the creature. */
	struct EquipItem {
		Common::UString resRef; ///< Name of the item blueprint resource.

		InventorySlot slot; ///< The equipment slot the item occupies.

		bool stealable; ///< Can this item be stolen?
		bool droopable; ///< Does this item drop with the creature's death?

		int32 setNumber; ///< ID of the set the item belongs to.
	};
	typedef std::vector<EquipItem> Items;

	typedef Common::PtrList<Graphics::Aurora::Model> Models;


	bool _isPC; ///< Is the creature a PC?

	/** The creature's appearance; index into the Appearances MGDA. */
	uint32 _appearanceID;
	/** The gender of the creature's model files. */
	uint8  _appearanceGender;

	/** Name of the morph file describing the creature's head. */
	Common::UString _headMorph;
	/** Indices into the MGDAs describing the creature's head model parts. */
	uint32 _partVariation[kPartVariationCount];

	/** All item the creature has currently equipped. */
	Items _items;

	/** The models making up this creature. */
	Models _models;


	void init();
	void load(const Aurora::GFF3Struct &placeable);
	void load(const Aurora::GFF3Struct &instance, const Aurora::GFF3Struct *blueprint);

	void loadProperties(const Aurora::GFF3Struct &gff);

	void loadModelsSimple(const Aurora::GDAFile &gda, size_t row);
	void loadModelsWelded(const Aurora::GDAFile &gda, size_t row);
	void loadModelsHead  (const Aurora::GDAFile &gda, size_t row);
	void loadModelsParts (const Aurora::GDAFile &gda, size_t row);

	void loadModelsHeadMorph(bool loadHair = true);
	void loadModelsHeadList(const Aurora::GDAFile &gda, size_t row, bool loadHair = true);

	Common::UString findEquipModel(InventorySlot slot, const Common::UString &prefix,
	                               uint8 *armorType = 0) const;

	static Common::UString createModelPrefix(const Aurora::GDAFile &gda, size_t row, uint8 gender);
	static Common::UString createModelPart(const Aurora::GDAFile &gda, size_t row,
	                                       const Common::UString &prefix);
};

} // End of namespace Dragon Age

} // End of namespace Engines

#endif // ENGINES_DRAGONAGE_CREATURE_H
