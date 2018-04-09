/*
** EPITECH PROJECT, 2021
** LibCaca
** File description:
** Created by kraken, 05/04/18 
*/

#ifndef LIBCACA_IDATABRIDGE_HPP
#define LIBCACA_IDATABRIDGE_HPP

#include <ILib.hpp>

namespace game
{
	class DataBridge
	{
	public:
		DataBridge() = default;
		virtual ~DataBridge() = default;

		grph::KeyEvent const& getEvent() const {
			return _event;
		}

		void setEvent(grph::KeyEvent const& event) {
			_event = event;
		}

	private:
		grph::KeyEvent _event{grph::NOTHING, 0};
	};
}

#endif //LIBCACA_IDATABRIDGE_HPP
