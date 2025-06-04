# SFMLProject
## Jumping Mechanic is Left From Ytb 
SFML 2.4 For Beginners - 13: Jumping.
## all the files with prefix '_' are made again for practise 


Two Buffer Working:
- *Back Buffer* : This is an off-screen buffer where all the drawing operations for the current frame take place.
	- You draw your sprites, shapes, text, etc., onto this buffer.
- *Front Buffer* : This is the buffer that is currently being displayed on the screen.

- Swapping (via window.display() in SFML): When you call window.display() in SFML, it essentially swaps the roles of the front and back buffers.
	- The back buffer, which now contains the complete rendered frame, becomes the front buffer and is displayed.
	- The old front buffer becomes the new back buffer, ready for the next frame's drawing.

This process ensures that the user only sees fully rendered frames, preventing issues where a partially drawn image might be displayed, leading to a "tearing" effect.


```
window.draw(player)
window.display();
```


***window.clear()***

The provided text explains a common issue in game development where objects appear to "drag" or leave trails when they move. 
	This happens because the screen isn't being cleared before each new frame is drawn. 
	The solution is to call window.clear() at the beginning of each frame, before drawing anything else. 
	This resets the screen, preventing the overlapping of previous frames and resulting in smooth movement
	
```
window.clear();
```


***KEYBOARD***
		the left_top Position is { 0.0f, 0.0f }

1. event->getIf<sf::Event::KeyPressed>()

	- Event-based input, When key first goes down (one-time event)
	- Use case -> Menu Trigger, One-Shot Trigger, AUDIO..

```
if (const auto* keyPressed = evnt->getIf<sf::Event::KeyPressed>()) 
{
	auto keyscancode = keyPressed->scancode;
	if (keyscancode == sf::Keyboard::Scancode::W) {
		std::cout << " -W- ";
		player.move({0,-1});
	}
}
```


2. sf::Keyboard::isKeyPressed(...)

	- Real-time input, While key is held down (continuous)
	- Use Case -> Character Movement..

```
if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::W)) {
		std::cout << " -W- ";
		player.move({ 0,-1 });
	}
```

 KEYS
- in SFML 3, when you press a key, you may see four different event types depending on context and configuration.

	- sf::Event::KeyPressed
	- sf::Event::KeyReleased
	- sf::Event::TextEntered
	- sf::Event::KeyboardUpdated -> maybe 

 MOUSE
```
if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) 
{
	sf::Vector2i mousePos = sf::Mouse::getPosition(window);
	player.setPosition(sf::Vector2f (mousePos));
//	player.setPosition({ static_cast<float> (mousePos.x), static_cast<float> (mousePos.y) });
}
```
	
- sf::Mouse::getPosition() -> Get the current position of the mouse in desktop coordinates.
	- return_type = sf::vector2i
- sf::Mouse::getPosition(const WindowBase &relative_to) -> Get the current position of the mouse in window coordinates.


sf::IntRect(left, top, width, height) defines the rectangle area in the texture's coordinate space (pixels).
	left and top = top-left corner (x, y)
	width and height = size of the cropped area


 ANIMATION !)!
	1. Idle Animation
	2. Walking Animation (left,right) -> can flip
