#pragma once

namespace sbt
{
	template <typename T>
	class Singleton
	{
	public:
		Singleton() { }
		Singleton(const Singleton&) = delete;
		Singleton(Singleton&&) = delete;
		~Singleton() { }
		Singleton& operator=(const Singleton&) = delete;
		Singleton& operator=(Singleton&&) = delete;

		[[nodiscard]] inline static T* getInstance()
		{
			static auto instance = std::make_shared<T>();
			return instance.get();
		}

	};
}