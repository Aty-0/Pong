#include "GameObject.h"
#include "core/Logger.h"

namespace sbt
{
	GameObject::GameObject() : m_scale({ 1.0f, 1.0f }), m_draw(true)
	{

	}

	GameObject::~GameObject() 
	{
		SAFE_DELETE(m_drawable);
	}

	void GameObject::update(float deltaTime)
	{
		onUpdate(deltaTime);
	}

	void GameObject::render(sf::RenderWindow& window)
	{
		if (!m_draw)
			return;

		renderDrawable(window);
		onRender(window);
	}

	void GameObject::keyPressed(sf::Event event)
	{
		onKeyPressed(event);
	}

	void GameObject::keyReleased(sf::Event event)
	{
		onKeyReleased(event);
	}

	void GameObject::updateHitBox()
	{
		m_hitBox.top = m_position.y;
		m_hitBox.left = m_position.x;
		m_hitBox.width = m_size.x * m_scale.x;
		m_hitBox.height = m_size.y * m_scale.y;
	}

	void GameObject::renderDrawable(sf::RenderWindow& window)
	{
		if (m_drawable)
		{
			window.draw(*m_drawable);
		}
	}

	void GameObject::setPosition(sf::Vector2f position)
	{
		m_position = position;
		updateHitBox();

		auto* transformable = dynamic_cast<sf::Transformable*>(m_drawable);
		if (transformable == nullptr)
		{
			ERR("Can't cast a drawable structure, maybe you trying to use an drawable explicitly! So, we can't set transform variables for it");
			return;
		}


		transformable->setPosition(m_position);
	}

	void GameObject::setColor(sf::Color color)
	{
		m_color = color;
		auto* shape = dynamic_cast<sf::Shape*>(m_drawable);

		if (shape)
		{
			shape->setOutlineColor(sf::Color::Transparent);
			shape->setFillColor(m_color);
			shape->setOutlineThickness(5);
			return;
		}

		auto* text = dynamic_cast<sf::Text*>(m_drawable);
		if (text)
		{
			text->setFillColor(m_color);
		}
	}

	void GameObject::setScale(sf::Vector2f scale)
	{
		m_scale = scale;
		updateHitBox();

		auto* transformable = dynamic_cast<sf::Transformable*>(m_drawable);
		if (transformable == nullptr)
		{
			ERR("Can't cast a drawable structure, maybe you trying to use an drawable explicitly! So, we can't set transform variables for it");
			return;
		}

		transformable->setScale(m_scale);
	}

	void GameObject::setSpeed(float speed)
	{
		m_speed = speed;
	}

	void GameObject::setSize(sf::Vector2f size)
	{
		m_size = size;
		updateHitBox();

		// Note: size is exist only for RectangleShape 		
		auto* rectangleShape = dynamic_cast<sf::RectangleShape*>(m_drawable);
	
		if(rectangleShape)
			rectangleShape->setSize(m_size);
	}

	void GameObject::setDraw(bool draw)
	{
		m_draw = draw;
	}

	bool GameObject::detectCollision(GameObject* go)
	{
		// Don't check collision with themself
		if (this == go)
			return false;

		if (m_hitBox.intersects(go->m_hitBox))
		{
			onDetectCollision();
			return true;
		}
		return false;
	}

	sf::Vector2<float>  GameObject::getPosition() const
	{
		return m_position;
	}

	sf::Vector2<float>  GameObject::getSize() const
	{
		return m_size;
	}

	sf::Vector2<float>  GameObject::getScale() const
	{
		return m_scale;
	}

	sf::FloatRect	    GameObject::getHitBox() const
	{
		return m_hitBox;
	}

	bool GameObject::isDrawn() const
	{
		return m_draw;
	}

	float GameObject::getSpeed() const
	{
		return m_speed;
	}

	sf::Color GameObject::getColor() const
	{
		return m_color;
	}

	sf::Drawable* GameObject::getDrawable() const
	{
		return m_drawable;
	}
}
