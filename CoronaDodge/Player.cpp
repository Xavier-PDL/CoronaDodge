#include "Player.h"
#include "World.h"
Player::Player()
	:
	Entity(EntType::ET_Player)
{
	playerSpray.setPointCount(3);
	playerSpray.setPoint(0, { 0, 0 });
	playerSpray.setPoint(1, { -25, -75 });
	playerSpray.setPoint(2, { 25, -75 });
	playerSpray.setFillColor(sf::Color::Cyan);
}

void Player::update(sf::Vector2f deltaPos)
{
	checkWall(deltaPos);
	checkStreaks(deltaPos);
	this->move(deltaPos);
	playerSpray.setPosition(getPosition());	
}

//hardcoded again..
void Player::checkWall(sf::Vector2f &deltaPos) {
	if (this->getPosition().x <= 200 + this->getLocalBounds().width / 2 && deltaPos.x < 0)
		deltaPos.x = 0;
	else if (this->getPosition().x >= 1000 - this->getLocalBounds().width / 2 && deltaPos.x > 0)
		deltaPos.x = 0;
	if (this->getPosition().y <= 150 + this->getLocalBounds().height / 2 && deltaPos.y < 0)
		deltaPos.y = 0;
	else if (this->getPosition().y >= 750 - this->getLocalBounds().height / 2 && deltaPos.y > 0)
		deltaPos.y = 0;
}

struct StreakCollision
{
	bool bCollided;
	sf::Vector2f* deltaPos;
	Player* player;
};

float sign(sf::Vector2f p1, sf::Vector2f p2, sf::Vector2f p3)
{
	return (p1.x - p3.x) * (p2.y - p3.y) - (p2.x - p3.x) * (p1.y - p3.y);
}

bool PointInTriangle(sf::Vector2f pt, sf::Vector2f v1, sf::Vector2f v2, sf::Vector2f v3)
{
	float d1, d2, d3;
	bool has_neg, has_pos;

	d1 = sign(pt, v1, v2);
	d2 = sign(pt, v2, v3);
	d3 = sign(pt, v3, v1);

	has_neg = (d1 < 0) || (d2 < 0) || (d3 < 0);
	has_pos = (d1 > 0) || (d2 > 0) || (d3 > 0);

	return !(has_neg && has_pos);
}

void checkCollision(Node<Entity>* pNode, void* pCollisionInfo)
{
	auto pInfo = reinterpret_cast<StreakCollision*>(pCollisionInfo);
	if (pInfo->bCollided)
		return;
	auto pPlayer = pInfo->player;
	auto pStreak = pNode->pElement;
	auto streakVerts = pStreak->getVerts();
	auto newPos = pPlayer->getPosition() + *pInfo->deltaPos;
	sf::Vector2f vertPos[] = {
		streakVerts[0].position,
		streakVerts[1].position,
		streakVerts[2].position,
		//streakVerts[3].position
	};
	auto bbox = pPlayer->getLocalBounds();
	sf::Vector2f hs = { bbox.width / 2, bbox.height / 2 };
	sf::Vector2f tr = { newPos.x + hs.x, newPos.y - hs.y };
	sf::Vector2f tl = { newPos.x - hs.x, newPos.y - hs.y };
	sf::Vector2f br = { newPos.x + hs.x, newPos.y + hs.y };
	sf::Vector2f bl = { newPos.x - hs.x, newPos.y + hs.y };
	if (PointInTriangle(tr, vertPos[0], vertPos[1], vertPos[2]))
	{
		pInfo->bCollided = true;
		
		pInfo->deltaPos->x *= -200;
		pInfo->deltaPos->y *= -200;
		pPlayer->move(*pInfo->deltaPos);
		pInfo->deltaPos->x *= 0;
		pInfo->deltaPos->y *= 0;
		
		return;
	}

	if (PointInTriangle(tl, vertPos[0], vertPos[1], vertPos[2]))
	{
		pInfo->bCollided = true;
		pInfo->deltaPos->x *= -200;
		pInfo->deltaPos->y *= -200;
		pPlayer->move(*pInfo->deltaPos);
		pInfo->deltaPos->x *= 0;
		pInfo->deltaPos->y *= 0;
		return;
	}

	if (PointInTriangle(br, vertPos[0], vertPos[1], vertPos[2]))
	{
		pInfo->bCollided = true;
		pInfo->deltaPos->x *= -200;
		pInfo->deltaPos->y *= -200;
		pPlayer->move(*pInfo->deltaPos);
		pInfo->deltaPos->x *= 0;
		pInfo->deltaPos->y *= 0;
		return;
	}

	if (PointInTriangle(bl, vertPos[0], vertPos[1], vertPos[2]))
	{
		pInfo->bCollided = true;
		pInfo->deltaPos->x *= -200;
		pInfo->deltaPos->y *= -200;
		pPlayer->move(*pInfo->deltaPos);
		pInfo->deltaPos->x *= 0;
		pInfo->deltaPos->y *= 0;
		return;
	}
}

void Player::checkStreaks(sf::Vector2f& deltaPos)
{
	auto pEnts = EntityManager::Get();
	auto streaks = pEnts->getStreaks();
	StreakCollision sc;
	sc.bCollided = false;
	sc.deltaPos = &deltaPos;
	sc.player = this;
	streaks.forEach(checkCollision, &sc);
}

void Player::updateSpray(float sprayAngle)
{
	playerSpray.setRotation(sprayAngle);
	isSpraying = sf::Mouse::isButtonPressed(sf::Mouse::Left);
}

void Player::draw(sf::RenderWindow& wnd)
{
	if(isSpraying)
		wnd.draw(playerSpray);
	wnd.draw(*this);
}

void Player::die()
{
	alive = false;
}

bool Player::isAlive()
{
	return alive;
}
