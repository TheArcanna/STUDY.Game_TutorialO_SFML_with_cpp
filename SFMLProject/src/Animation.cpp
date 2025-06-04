#include "Animation.h"
#include <iostream>
#include <SFMl/Graphics.hpp>

Animation::Animation(sf::Texture *texture, sf::Vector2u imageCount, float switchTime)
{
	this->ImageCount = imageCount;
	this->switchTime = switchTime;
	this->totalTime = 0.0f;
	this->currentImage.x = 0;
	
	sf::Vector2u textureSize = texture->getSize();

	int newBox_TextureSize_x = static_cast<int> (textureSize.x / imageCount.x);
	int newBox_TextureSize_y = static_cast<int> (textureSize.y / imageCount.y);

	uvRect.size = sf::Vector2i({ newBox_TextureSize_x, newBox_TextureSize_y });

}
Animation::~Animation() {

}

void Animation::Update(int row, float deltaTime, bool faceChange) 
{
	this->currentImage.y = row;
	this->totalTime += deltaTime;

	if (totalTime >= switchTime) 
	{
		totalTime -= switchTime;
		currentImage.x++;

		if (currentImage.x >= ImageCount.x)
		{
			currentImage.x = 0;
		}
	}
	
	uvRect.position.y = static_cast<int> (currentImage.y * uvRect.size.y);
//	if the sprite should be displayed in its original orientation(faceChange is True) or flipped(faceChange is false)
	if (faceChange) {
		uvRect.position.x = static_cast<int> (currentImage.x * uvRect.size.x);
		uvRect.size.x = std::abs(uvRect.size.x);
	}
	else {
		uvRect.position.x = static_cast<int> ((currentImage.x + 1) * (std::abs(uvRect.size.x)));
		uvRect.size.x = (-std::abs(uvRect.size.x));
	}
}

/* 1. The Concept of 2D Animation :
   - It's explained as switching between different images from a sprite sheet over time.
   - The example uses a sprite sheet of Tux (the Linux penguin) where each row represents a different animation (idle, dying, jumping, etc.).

2. The `Animation` Class:**
   # **Private Variables:**
	 - `sf::Vector2u imageCount`: Stores the number of images in each row and the total number of rows in the sprite sheet for the current animation.
	 - `sf::Vector2u currentImage`: Tracks the current frame being displayed within the animation (x for column, y for row).
	 - `float totalTime`: Accumulates the time since the last frame switch.
	 - `float switchTime`: Defines the duration (in seconds) between each frame change.
	 - `sf::IntRect uvRect`: Represents the portion of the texture to be displayed for the current frame of the animation (the "UV" or texture coordinates). This is made public.
	# **Constructor**
```
	Animation::Animation(sf::Texture *texture, sf::Vector2u ImageCount, float switchTime)
	{
		this->ImageCount = ImageCount;
		this->switchTime = switchTime;
		this->totalTime = 0.0f;
		this->currentImage.x = 0;

		sf::Vector2u textureSize = texture->getSize();

		int newBox_TextureSize_x = static_cast<int> (textureSize.x / ImageCount.x);
		int newBox_TextureSize_y = static_cast<int> (textureSize.y / ImageCount.y);

		uvRect.size = sf::Vector2i({ newBox_TextureSize_x, newBox_TextureSize_y });

	}

```

   # **`update()` Function:**
	 - Takes an `int row` (the animation row to play) and `float deltaTime` (the time elapsed since the last frame).
	 - If `totalTime` is greater than or equal to `switchTime`:
	   - Subtracts `switchTime` from `totalTime` (for smoother animation).
	   - Increments `currentImage.x` to move to the next frame in the row.
	   - If `currentImage.x` goes beyond the number of images in the row (`imageCount.x`), it resets `currentImage.x` to 0 to loop the animation.
	   - Updates the `uvRect.left` and `uvRect.top` to select the correct sprite from the sprite sheet based on `currentImage.x`, `currentImage.y`, and the calculated sprite width and height.

```
	void Animation::Update(int row, float deltaTime)
	{
		this->currentImage.y = row;
		this->totalTime += deltaTime;

		if (totalTime >= switchTime)
		{
			totalTime -= switchTime;
			currentImage.x++;

			if (currentImage.x >= ImageCount.x)
			{
				currentImage.x = 0;
			}
		}

		uvRect.position.x = static_cast<int> (currentImage.x * uvRect.size.x);
		uvRect.position.y = static_cast<int> (currentImage.y * uvRect.size.y);

	}

```
*//*

3. Using the `Animation` Class in `main.cpp`:**
   - An `Animation` object named `animation` is created.
   - It's initialized with a `playerTexture`, the `imageCount` (3 frames wide, 9 rows high from the sprite sheet), and a `switchTime` of 0.3 seconds.
   
   - A `sf::Clock` is used to calculate `deltaTime` in each frame of the main loop.
   - The `animation.update()` function is called with the desired animation row (0 for the "idle" animation) and the `deltaTime`.
   - The `player` sprite's texture rectangle (`setTextureRect`) is set to the `animation.uvRect` to display the current frame of the animation.
   - The background clear color is changed to gray.


```
// IN MAIN,
	Animation playerAnimation(&playerTexture, sf::Vector2u({ 5,2 }), 0.1f);

	float deltaTime;
	sf::Clock clock

// INSIDE while(window.isOpen()) LOOP,
		deltaTime = clock.restart().asSeconds();



		playerAnimation.Update(0, deltaTime);
		player.setTextureRect(playerAnimation.uvRect);
		
		window.clear();
```


**In essence, this code creates a system to play 2D animations from a sprite sheet by:**

- Knowing how the sprite sheet is organized (number of images per row/column).
- Keeping track of the current frame being displayed.
- Switching to the next frame after a set amount of time (`switchTime`), using `deltaTime` for frame-rate independence.
- Updating the texture rectangle of a sprite to show the correct portion of the sprite sheet for the current animation frame.

*/