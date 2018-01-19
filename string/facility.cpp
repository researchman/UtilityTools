#include "stdafx.h"
#include "facility.h"
#include <fstream>

std::vector<std::string> utility::string_facility::Split(const string& source, const string& delim, bool ignored)
{
	//�������շָ����ַ���
	std::vector<std::string> ret;
	ret.resize(0);

	std::string value = source;
	//�����ֵ����зָ������滻��Ϊһ����ͬ���ַ����ָ����ַ����ĵ�һ����  
	std::replace_if(value.begin(), value.end(), [&](const char& c) {if (delim.find(c) != std::string::npos) { return true; } else { return false; }}, delim.at(0));
	//�ҵ���һ���ָ�����λ��
	size_t pos = value.find(delim.at(0));
	std::string addedString = "";
	while (pos != std::string::npos) {
		//��ȡ�ַ���
		addedString = value.substr(0, pos);
		if (!addedString.empty() || !ignored) {
			ret.push_back(addedString);
		}
		//������ȡ���ַ���
		value.erase(value.begin(), value.begin() + pos + 1);
		pos = value.find(delim.at(0));
	}
	//
	addedString = value;
	if (!addedString.empty() || !ignored) {
		ret.push_back(addedString);
	}

	return std::move(ret);
}

std::map<int, point::YPoint<double>> utility::file_facility::LoadData()
{
	ifstream in;
	in.open("D:/position.log");

	if (!in.is_open())
	{
		return std::map<int, point::YPoint<double>>();
	}

	char pch[200] = { 0 };

	std::map<int, point::YPoint<double>> ret;

	while (!in.eof())
	{
		in.getline(pch, 200);
		string data = pch;

		std::vector<std::string> metaDatas = utility::string_facility::Split(data, ",", true);

		std::string card_id = "";
		unsigned int card_ct = 0;
		point::YPoint<double> p;
		for (unsigned int i = 0; i < metaDatas.size(); i++)
		{
			std::string meta = metaDatas[i];
			std::vector<std::string> vtMeta = utility::string_facility::Split(meta, ":", true);
			switch (i) {
			case 0:
			{
				//����
				card_id = vtMeta[1];
				break;
			}
			case 1:
				//����ct��
				card_ct = atoi(vtMeta[1].c_str());
				break;
			case 2:
				//x
				p.x = atof(vtMeta[1].c_str());
				break;
			case 3:
				//y
				p.y = atof(vtMeta[1].c_str());
				break;
			case 4:
				//��վ��
				break;
			default:
				break;
			}
		}

		ret.insert(std::make_pair(card_ct, p));
	}
	in.close();

	return std::move(ret);
}

point::YPoint<double> utility::geometry_facility::Circle(point::YPoint<double>& p1, point::YPoint<double>& p2, point::YPoint<double>& p3, double & radius)
{
	double x1 = p1.x, x2 = p2.x, x3 = p3.x;
	double y1 = p1.y, y2 = p2.y, y3 = p3.y;
	double a = x1 - x2;
	double b = y1 - y2;
	double c = x1 - x3;
	double d = y1 - y3;
	double e = ((x1 * x1 - x2 * x2) + (y1 * y1 - y2 * y2)) / 2.0;
	double f = ((x1 * x1 - x3 * x3) + (y1 * y1 - y3 * y3)) / 2.0;
	double det = b * c - a * d;

	point::YPoint<double> p;

	if (fabs(det) < 1E-5)
	{
		radius = -1;
		return std::move(p);
	}

	double x0 = -(d * e - b * f) / det;
	double y0 = -(a * f - c * e) / det;
	radius = hypot(x1 - x0, y1 - y0);
	p.x = x0;
	p.y = y0;

	return std::move(p);
}

bool utility::geometry_facility::IsOnStraightLine(point::YPoint<double>& p1, point::YPoint<double>& p2, point::YPoint<double>& p3)
{
	//��Y����
	if (fabs(p1.x - p2.x) < 1E-4 && fabs(p2.x - p3.x) < 1E-4)
	{
		return true;
	}

	//��X����
	if (fabs(p1.y - p2.y) < 1E-4 && fabs(p2.y - p3.y) < 1E-4)
	{
		return true;
	}

	//б��Ϊk
	double k1 = (p1.y - p2.y) / (p1.x - p2.x);
	double k2 = (p2.y - p3.y) / (p2.x - p3.x);

	if (fabs(fabs(k1) - fabs(k2)) < 1E-4)
	{
		return true;
	}

	return false;
}
