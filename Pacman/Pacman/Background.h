#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "S2D/S2D.h"

class Background final
{
public:
	Background() = delete;
	Background(const unsigned int spritesOnWidth = 14, const unsigned int spritesOnHeight = 3);
	~Background();

	void			Render();
	void		    Update();

	const char**    GetCollisionMap()    { return (const char**)mCollisionMap; }
	unsigned int    GetCollisionWidth()  { return mWidth;  }
	unsigned int    GetCollisionHeight() { return mHeight; }

	void            ChangeColourIndex(const unsigned int newIndex);

private:
	void            LoadInCollisionMap();
	void            LoadInBackgroundSpriteMap();

	char**          mCollisionMap;
	unsigned int**  mBackgroundSpriteMap;

	S2D::Rect*      mSpriteSheetSourceRenderRect;
	S2D::Rect*      mSpriteSheetDestRenderRect;

	unsigned int    mSingleTileWidth;
	unsigned int    mSingleTileHeight;

	S2D::Texture2D* mTileSpriteSheet;

	unsigned int    mHeight;
	unsigned int    mWidth;

	unsigned int    mAmountOfSpritesOnSpriteSheetWidth;
	unsigned int    mAmountOfSpritesOnSpriteSheetHeight;

	unsigned int    mColourIndex;

	bool            mButtonCurrentlyPressed;
};

#endif