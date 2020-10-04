#include "pch.h"

#include "gui/CatHelper.h"
#include "gui/CatReaction.h"

#include <QMovie>
#include "tools/CatHelperSerializer.h"

CatHelper::CatHelper(QWidget * parent)
	: QWidget(parent)
	, m_generator(m_random())
{
	ui.setupUi(this);
}

void CatHelper::SetReaction(CatReaction reaction)
{
	auto it = m_reactions.find(reaction);
	if (it == m_reactions.end())
	{
		assert(!"Incorrect cat reaction!");
		return;
	}

	auto && [_, data] = *it;
	if (!data || data->images.empty())
	{
		assert(!"Image for chosen reaction does not found!");
		return;
	}

	size_t imageIndex = Random(0, data->images.size());
	vector<string> images {data->images.begin(), data->images.end()};
	SetImage(images[imageIndex]);

	if (!data->texts.empty())
	{
		size_t textIndex = Random(0, data->texts.size());
		vector<std::wstring> texts {data->texts.begin(), data->texts.end()};
		SetText(texts[textIndex]);
	}
	else
	{
		SetText(L"");
	}
}

void CatHelper::Save(const string& filename)
{
	auto serializer = CatHelperSerializer(this);
	if (!serializer.Save(filename))
	{
		qDebug() << QString::fromStdString(serializer.Error());
	}
}

void CatHelper::resizeEvent(QResizeEvent* event)
{
	SetImage(m_chosenImage);
	QWidget::resizeEvent(event);
}

void CatHelper::SetText(const std::wstring& text)
{
	ui.textLabel->setText(QString::fromStdWString(text));
}

int CatHelper::Random(int from, int to) const
{
	std::uniform_int_distribution<int> dist {from, to - 1};
	return dist(m_generator);
}

void CatHelper::AddToReactions(CatReaction reaction, set<string> images, set<std::wstring> texts)
{
	auto it = m_reactions.find(reaction);
	if (it == m_reactions.end())
	{
		auto [addedIt, success] = m_reactions.emplace(reaction, make_shared<CatReactionData>());
		it = addedIt;
	}

	auto && [_, data] = *it;
	data->images.merge(images);
	data->texts.merge(texts);
}

void CatHelper::Walk(std::function<void(CatReaction, shared_ptr<const CatReactionData>)> callback) const
{
	for (auto && [reaction, pData] : m_reactions)
	{
		callback(reaction, std::const_pointer_cast<const CatReactionData>(pData));
	}
}

void CatHelper::Load(const string& filename)
{
	auto backup_reactions = m_reactions;
	
	auto serializer = CatHelperSerializer(this);
	serializer.Load(filename);
	
	if (auto error = serializer.Error(); !error.empty())
	{
		qDebug() << QString::fromStdString(serializer.Error());
		m_reactions = backup_reactions;
	}
}

void CatHelper::SetImage(const string& imageName)
{
	if (imageName == m_chosenImage)
	{
		// если картинка с запрошенным названием уже загружена, то ничего не делаем
		return;
	}
	
	auto resourceName = QString(":/reaction_images/%1").arg(imageName.c_str());
	bool isGif = imageName.find(".gif") != imageName.npos;
	
	if (!isGif) // статическая картинка:
	{
		if (auto movie = ui.imageLabel->movie())
		{
			// Если до этого была запущена картинка, то стопает её
			movie->stop();
			movie->deleteLater();
		}
		
		auto pixmap = QPixmap(resourceName);
		if (pixmap.isNull())
		{
			assert(!"Cannot load image!");
			return;
		}
		auto scaled = pixmap.scaled(ui.imageLabel->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
		ui.imageLabel->setPixmap(scaled);
	}
	else // гифка:
	{
		// Если до этого была запущена гифка, то останавливаем и удаляем её
		if (auto movie = ui.imageLabel->movie())
		{
			movie->stop();
			movie->deleteLater();
		}
		if (auto movie = new QMovie(resourceName, "gif", this))
		{
			movie->setScaledSize(ui.imageLabel->size());
			if (!movie->isValid())
			{
				assert(!"Cannot load gif!");
				return;
			}
			ui.imageLabel->setMovie(movie);
			movie->start();	
		}
	}
	
	m_chosenImage = imageName;
}
