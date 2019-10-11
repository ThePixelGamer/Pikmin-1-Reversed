#include "SRTNode.h"
#include "../AgeServer.h"

SRTNode::SRTNode(char*) : Node() {
	Vector3f pos(0.0, 0.0, 0.0);
	setPosition(pos);

	Vector3f rot(1.0, 1.0, 1.0);
	setRotation(rot);

	Vector3f sc(0.0, 0.0, 0.0);
	setScale(sc);
}

void SRTNode::update()
{
	for (Node* i = static_cast<Node*>(this->child); i; i = static_cast<Node*>(i->next))
	{
		if (i->getFlag(1))
		{
			i->concat(this->m_mat4f);
			i->update();
		}
	}
}

void SRTNode::concat() { }
void SRTNode::concat(Matrix4f&) { }

Matrix4f* SRTNode::getModelMatrix()
{
	return &this->m_mat4f;
}

void SRTNode::genAge(AgeServer& server)
{
	server.StartSection("SRTNode", true);

	Vector3f ScaleUpperBounds(2.0f, 2.0f, 2.0f);
	Vector3f ScaleLowerBounds(0.0f, 0.0f, 0.0f);
	this->m_srt.m_scale.genAge(server, "S", ScaleUpperBounds, ScaleLowerBounds);

	Vector3f RotationUpperBounds(3.1415927f, 3.1415927f, 3.1415927f);
	Vector3f RotationLowerBounds(-3.1415927f, -3.1415927f, -3.1415927f);
	this->m_srt.m_rotation.genAge(server, "R", RotationUpperBounds, RotationLowerBounds);

	Vector3f TransformUpperBounds(1000.0f, 1000.0f, 1000.0f);
	Vector3f TransformLowerBounds(-1000.0f, -1000.0f, -1000.0f);
	this->m_srt.m_rotation.genAge(server, "T", TransformUpperBounds, TransformLowerBounds);

	server.EndSection();
	this->genAge(server);
}

Vector3f * SRTNode::getPosition()
{
	return &this->m_srt.m_position;
}

Vector3f* SRTNode::getRotation()
{
	return &this->m_srt.m_rotation;
}

Vector3f* SRTNode::getScale()
{
	return &this->m_srt.m_scale;
}

Vector3f* SRTNode::getWorldPosition()
{
	return reinterpret_cast<Vector3f*>(this->m_mat4f.mMatrix4f[3]);
}

void SRTNode::setPosition(Vector3f & pos)
{
	this->m_srt.m_position = pos;
}

void SRTNode::setRotation(Vector3f & rot)
{
	this->m_srt.m_rotation = rot;
}

void SRTNode::setScale(Vector3f & sca)
{
	this->m_srt.m_scale = sca;
}