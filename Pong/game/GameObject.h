#pragma once
#include "core/common.h"
namespace sbt
{
	class GameObject
	{
	public:
		GameObject();
		~GameObject();


		bool detectCollision(GameObject* go);
		void update(float deltaTime);
		void render(sf::RenderWindow& window);
		void keyPressed(sf::Event event);
		void keyReleased(sf::Event event);
		void setSpeed(float speed);
		void setPosition(sf::Vector2f position);
		void setScale(sf::Vector2f scale);
		// Shape size 
		void setSize(sf::Vector2f size);
		void setDraw(bool draw);
		void setColor(sf::Color color);

		[[nodiscard]] sf::Vector2<float> getPosition() const;
		[[nodiscard]] sf::Vector2<float> getSize() const;
		[[nodiscard]] sf::Vector2<float> getScale() const;
		[[nodiscard]] sf::FloatRect	   getHitBox() const;
		[[nodiscard]] sf::Color		   getColor() const;
		[[nodiscard]] float			   getSpeed() const;
		[[nodiscard]] bool			   isDrawn() const;
		[[nodiscard]] sf::Drawable* getDrawable() const;

	protected:
		virtual void onDetectCollision() { }
		virtual void onUpdate(float deltaTime) { }
		virtual void onRender(sf::RenderWindow& window) { }
		virtual void onKeyPressed(sf::Event event) { }
		virtual void onKeyReleased(sf::Event event) { }

	private:
		void renderDrawable(sf::RenderWindow& window);
		void updateHitBox();
		
		sf::Vector2<float> m_position;
		sf::Vector2<float> m_size;
		sf::Vector2<float> m_scale;
		sf::FloatRect	   m_hitBox;
		float			   m_speed;
		sf::Drawable*	   m_drawable;
		sf::Color		   m_color;
		bool			   m_draw;
	public:
		template<typename T>
		T* createDrawableWithType()
		{
			// FIXME:
			//static_assert(!std::is_base_of<T, sf::Drawable>::value || 
			//	std::is_same<T, sf::Drawable>::value, "Must be based on a drawable class");

			m_drawable = new T();
			return reinterpret_cast<T*>(m_drawable);
		}

	};
}