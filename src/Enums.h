#pragma once

enum class ComponentType
{
	DrawingComponent
};

enum class MapObjectType
{
	Grass,
	Sky,
};

enum class Direction
{
	Up,
	Down,
	Right,
	Left
};

enum class GameObjectTag
{
	Player,
	Enemy
};

enum class CollisionType
{
	ReceiveDamage,
	DealDamage
};