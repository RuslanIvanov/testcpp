#pragma once
class human 
{
	bool m_bLive;
	size_t count_childs;
	std::string m_name;
	std::pair<shared_ptr<human>, shared_ptr<human>> parent;
	std::vector<weak_ptr<human>> childs;
public:
	human(const std::pair<shared_ptr<human>, shared_ptr<human>>& p) 
	{
	}

	human(const std::shared_ptr<human>& p)
	{
	}

	human(const weak_ptr<human>& c)
	{
	}

	static  weak_ptr<human>& child(const char* c) 
	{
	}
};