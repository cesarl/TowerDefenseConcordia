#pragma once

#include <functional>
#include <vector>
#include <memory>

#include "Message.hpp"

namespace TDC
{
	class Publisher;

	class Subscriber
	{
	public:
		template <typename T>
		void subcribeToMessage(std::function<void(const IMessage *message)> function)
		{
			if (_callbacks.size() <= T::getId())
			{
				_callbacks.resize(T::getId() + 1);
			}
			_callbacks[T::getId()] = function;
		}

		template <typename T>
		void unsubcribeToMessage()
		{
			if (_callbacks.size() <= T::getId())
			{
				return;
			}
			_callbacks[T::getId()] = nullptr;
		}

		struct Handle
		{
			Subscriber *ptr;
			bool valid;
			Handle(Subscriber *_ptr, bool _valid)
				: ptr(_ptr)
				, valid(_valid)
			{}
		};

		Subscriber()
		{
			_handle = std::make_shared<Handle>(this, true);
		}

		virtual ~Subscriber()
		{
			_handle->valid = false;
		}

		inline const std::shared_ptr<Handle> getHandle() const
		{
			return _handle;
		}

	private:
		bool receive(const IMessage *message)
		{
			if (message->getTypeId() >= _callbacks.size())
				return false;
			if (!_callbacks[message->getTypeId()])
				return false;
			_callbacks[message->getTypeId()](message);
			return true;
		}

		std::vector<std::function<void(const IMessage *message)>> _callbacks;
		std::shared_ptr<Handle> _handle;

		friend class Publisher;
	};

	class Publisher
	{
	public:
		Publisher()
		{}

		~Publisher()
		{}

		template <class T, typename... Args>
		void publish(Args ...args)
		{
			T tmp(args...);
			for (auto &e : _subscribers)
			{
				e->ptr->receive(&tmp);
			}
		}

		void addSubscriber(std::shared_ptr<Subscriber::Handle> handle)
		{
			for (auto &e : _subscribers)
			{
				if (e->ptr == handle->ptr)
					return;
			}
			_subscribers.push_back(handle);
		}

		void removeSubscriber(std::shared_ptr<Subscriber::Handle> handle)
		{
			for (auto i = 0; i < _subscribers.size(); ++i)
			{
				if (_subscribers[i]->ptr == handle->ptr)
				{
					std::swap(_subscribers[i], _subscribers.back());
					_subscribers.pop_back();
					return;
				}
			}
		}

		void removeEmptySubscribers()
		{
			for (auto i = 0; i < _subscribers.size(); ++i)
			{
				if (!_subscribers[i]->valid)
				{
					std::swap(_subscribers[i], _subscribers.back());
					_subscribers.pop_back();
					return;
				}
			}
		}

	private:
		std::vector<std::shared_ptr<Subscriber::Handle>> _subscribers;
	};
}