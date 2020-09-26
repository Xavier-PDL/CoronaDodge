void drawArena(sf::RenderWindow& window) {
	/*
	Draws the arena as a white square with black border. This must be drawn before all other sprites or else they won't appear.
	*/
	sf::RectangleShape arena;
	unsigned int window_x = window.getSize().x;
	unsigned int window_y = window.getSize().y;
	arena.setSize(sf::Vector2f(window_x * .8f, window_y * .8f));
	arena.setOutlineColor(sf::Color::Black);
	arena.setOutlineThickness(window_x * .01f);
	arena.setPosition(window_x * .1f, window_y * .1f);
	window.draw(arena);
}