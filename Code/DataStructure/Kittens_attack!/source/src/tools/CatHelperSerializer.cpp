#include "pch.h"
#include "tools/CatHelperSerializer.h"

#include <fstream>
#include <locale>
#include <codecvt>

#include "gui/CatReaction.h"
#include "gui/CatHelper.h"
#include "nlohmann/json.hpp"

using nlohmann::json;

struct SerializableReaction
{
	CatReaction				reaction;	
	set<string>				images;
	set<std::wstring>		texts;
};

namespace details
{
	auto && GetEvents()
	{
		const static vector<std::pair<CatReaction::Event, string>> events =
		{
			{CatReaction::Event::FIRST_MEETING,					"on_open"},
			{CatReaction::Event::CLICK_ON_CAT,					"on_click"},
			{CatReaction::Event::INACTION_TIMEOUT_SMALL_1,		"on_small_timeout_1"},
			{CatReaction::Event::INACTION_TIMEOUT_SMALL_2,		"on_small_timeout_2"},
			{CatReaction::Event::INACTION_TIMEOUT_LONG,			"on_big_timeout"},
			{CatReaction::Event::HELP_READING_START,			"on_help_open_once"},
			{CatReaction::Event::HELP_READING_START_N,			"on_help_open_more"},
			{CatReaction::Event::HELP_READING_END,				"on_help_close"},
			{CatReaction::Event::INSERTION,						"on_insertion"},
			{CatReaction::Event::REMOVING,						"on_removing"},
			{CatReaction::Event::SEACH,							"on_search"},
			{CatReaction::Event::OUT_OF_RANGE_INDEX,			"on_incorrect_index"},
			{CatReaction::Event::INVALID_DATA,					"on_incorrect_data"},
		};
		return events;
	}
	
	auto && GetResults()
	{
		const static vector<std::pair<CatReaction::Result, string>> results =
		{
			{CatReaction::Result::SUCCESSED, "success"},
			{CatReaction::Result::FAILED, "fail"},
			{CatReaction::Result::IMPOSIBLE, "imposible"},
		};
		return results;
	}

	auto && GetContainerTypes()
	{
		const static vector<std::pair<CatReaction::ContainerType, string>> results =
		{
			{CatReaction::ContainerType::LIST, "success"},
			{CatReaction::ContainerType::STACK, "fail"},		
		};
		return results;
	}
	
	std::wstring Convert(const string & str)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.from_bytes(str);			
	}
	
	string Convert(const std::wstring & wstr)
	{
		std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
		return converter.to_bytes(wstr);
	}
}

const string & to_string(CatReaction::Event input_event)
{
	auto && events = details::GetEvents();
	for (auto && [event, event_name] : events)
	{
		if (event == input_event)
		{
			return event_name;
		}
	}
	
	assert(!"Unknown CatReaction::Event!");
	static const string empty;
	return empty;
}

CatReaction::Event event_from_string(const string & input_event)
{
	auto && events = details::GetEvents();
	for (auto && [event, event_name] : events)
	{
		if (event_name == input_event)
		{
			return event;
		}
	}
	
	assert(!"Unknown CatReaction::Event!");
	return CatReaction::Event::_COUNT;
}

const string & to_string(CatReaction::Result input_result)
{
	auto && results = details::GetResults();
	for (auto && [result, result_str] : results)
	{
		if (result == input_result)
		{
			return result_str;
		}
	}
	
	assert(!"Unknown CatReaction::Result!");
	static const string empty;
	return empty;
}

CatReaction::Result result_from_string(const string & input_result)
{
	auto && results = details::GetResults();
	for (auto && [result, result_str] : results)
	{
		if (result_str == input_result)
		{
			return result;
		}
	}
	
	assert(!"Unknown CatReaction::Result!");
	return CatReaction::Result::_COUNT;
}

const string & to_string(CatReaction::ContainerType input_container)
{
	auto && containters = details::GetContainerTypes();
	for (auto && [container, container_str] : containters)
	{
		if (container == input_container)
		{
			return container_str;
		}
	}
	
	assert(!"Unknown CatReaction::Result!");
	static const string empty;
	return empty;
}

CatReaction::ContainerType container_from_string(const string & input_container)
{
	auto && containers = details::GetContainerTypes();
	for (auto && [container, container_str] : containers)
	{
		if (container_str == input_container)
		{
			return container;
		}
	}
	
	assert(!"Unknown CatReaction::ContainerType!");
	return CatReaction::ContainerType::_COUNT;
}

void to_json(json & j, const CatReaction & reaction)
{
	j = json {
		{"event", to_string(reaction.event)}
	};
	
	if (reaction.result != CatReaction::Result::_COUNT)
	{
		j["result"] = to_string(reaction.result);
	}
	
	if (reaction.container != CatReaction::ContainerType::_COUNT)
	{
		j["container"] = to_string(reaction.container);
	}
}

void from_json(const json & j, CatReaction & reaction)
{
	auto event_it = j.find("event");
	if (event_it == j.end())
	{
		qDebug() << "Cannot find \"event\" data in json!";
		return;
	}

	reaction.event = event_from_string(event_it->get<string>());
	
	auto result_it = j.find("result");
	if (result_it != j.end())
	{
		reaction.result = result_from_string(result_it->get<string>());
	}
	
	auto container_it = j.find("container");
	if (container_it != j.end())
	{
		reaction.container = container_from_string(container_it->get<string>());
	}
}

void to_json(json & j, const SerializableReaction & object)
{
	set<string> texts;
	for (auto && wtext : object.texts)
	{
		texts.emplace(std::move(details::Convert(wtext)));
	}
	
	j = json {
		{"reaction", object.reaction},
		{"images", object.images},
		{"texts", texts},
	};
}

void from_json(const json & j, SerializableReaction & object)
{
	auto reaction_it = j.find("reaction");
	auto images_it = j.find("images");
	auto texts_it = j.find("texts");
	if (images_it == j.end())
	{
		qDebug() << "Cannot find \"images\" data in json!";
		return;
	}
	if (texts_it == j.end())
	{
		qDebug() << "Cannot \"texts\" data in json!";
		return;
	}
	if (reaction_it == j.end())
	{
		qDebug() << "Cannot \"reaction\" data in json!";
		return;
	}

	set<string> texts;
	
	reaction_it->get_to(object.reaction);		
	images_it->get_to(object.images);
	texts_it->get_to(texts);
	
	for (auto && text : texts)
	{
		object.texts.emplace(std::move(details::Convert(text)));
	}
}

struct CatHelperSerializer::Impl
{

	// adds reaction parsed from $json to $out and returns error string if some errors have been occurred
	string Parse(const json & json, CatHelper * out)
	{
		string error;
		for (auto && json_data : json)
		{
			try
			{
				auto data = json_data.get<SerializableReaction>();
				out->AddToReactions(data.reaction, data.images, data.texts);
			}
			catch (const json::exception & e)
			{
				error += string(e.what()) + "\n";
			}
		}

		// removing last '\n' (new line symbol)
		if (!error.empty())
		{
			error.pop_back();
		}
		
		return error;
	}
};

CatHelperSerializer::CatHelperSerializer(CatHelper * catHelper)
	: m_catHelper(catHelper)
	, m_pImpl(make_unique<Impl>())
{
	
}

CatHelperSerializer::~CatHelperSerializer()
{
}

bool CatHelperSerializer::LoadFromMemory(const char* data)
{
	if (!m_catHelper)
	{
		m_error = "Incorrect input parameter. \"CatHelper\" is empty!";
		return false;
	}
	
	json j;
	try
	{
		j = data;
	}
	catch (const json::exception & e)
	{
		m_error = e.what();
		return false;
	}
	
	m_error = m_pImpl->Parse(j, m_catHelper);
	
	return true;
}

bool CatHelperSerializer::Load(const string & filename)
{	
	if (!m_catHelper)
	{
		m_error = "Incorrect input parameter. \"CatHelper\" is empty!";
		return false;
	}
	
	json j;
	{
		std::ifstream input (filename);
		if (!input.is_open())
		{
			m_error = "Cannot open file \"" + filename + "\"!";
			return false;
		}

		try
		{
			input >> j;
			if (input.fail())
			{
				m_error = "Cannot load json data from \"" + filename + "\"!";
				return false;
			}
		}
		catch (const json::exception & e)
		{
			m_error = e.what();
			return false;
		}
	}

	m_error = m_pImpl->Parse(j, m_catHelper);
	
	return true;
}

bool CatHelperSerializer::Save(const string & filename)
{
	if (!m_catHelper)
	{
		m_error = "Incorrect input parameter. \"CatHelper\" is empty!";
		return false;
	}

	json j;
	auto walker = [&j](CatReaction reaction, shared_ptr<const CatReactionData> pData)
	{
		json && json_reaction = SerializableReaction{reaction, pData->images, pData->texts};
		j.emplace_back(std::move(json_reaction));
	};
	m_catHelper->Walk(walker);
	
	std::ofstream output (filename);
	if (!output.is_open())
	{
		m_error = "Cannot open file \"" + filename + "\"!";
		return false;
	}
	output << j.dump(1, '\t');
	
	if (output.fail())
	{
		m_error = "Cannot load json data from \"" + filename + "\"!";
		return false;
	}

	return true;
}
