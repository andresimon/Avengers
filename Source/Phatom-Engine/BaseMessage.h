#pragma once

enum eMessageType
{
	SetPosition,
	GetPosition,
};

class BaseMessage
{
	protected: // Abstract class, constructor is protected
		BaseMessage(int destinationObjectID, eMessageType messageTypeID)
			: m_destObjectID(destinationObjectID)
			, m_messageTypeID(messageTypeID)
		{}

	public: // Normally this isn't public, just doing it to keep code small
		int m_destObjectID;
		eMessageType m_messageTypeID;
};
