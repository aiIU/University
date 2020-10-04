#pragma once

#include "ui_CatHelper.h"
#include <random>

struct CatReaction;

struct CatReactionData
{
	set<string>				images;
	set<std::wstring>		texts;
};

class CatHelper : public QWidget
{
	Q_OBJECT
public:
	CatHelper(QWidget * parent = nullptr);

	void SetReaction(CatReaction reaction);

	void AddToReactions(CatReaction reaction, set<string> images, set<std::wstring> texts);
	void Walk(std::function<void(CatReaction, shared_ptr<const CatReactionData>)> callback) const;
	
	void Load(const string & filename);
	void Save(const string & filename);
	
private:	
	void resizeEvent(QResizeEvent* event) override;

	void SetImage(const string & imageName);
	void SetText(const std::wstring & text);
	int Random(int from, int to) const;

	Ui::CatHelper										ui;
	map<CatReaction, shared_ptr<CatReactionData>>		m_reactions;
	string												m_chosenImage;
	
	std::random_device									m_random;
	mutable std::mt19937								m_generator;
};
