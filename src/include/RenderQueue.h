#ifndef CLASS_NCINE_RENDERQUEUE
#define CLASS_NCINE_RENDERQUEUE

#include "RenderCommand.h"
#include "Array.h"
#include "StaticArray.h"

namespace ncine {

class SceneNode;

/// Traverse and flatten the scenegraph representation
/** This class is responsible for traversing the scenegraph
and creating a tree of render commands */
class RenderQueue
{
  public:
	RenderQueue();

	// Adds a draw command to the queue
	void addCommand(RenderCommand *command);
	// Sorts the queues then issues every render command in order
	void draw();

	/// Returns the total number of vertices to be rendered by the queue
	inline unsigned int numVertices() const { return lastNumVertices_; }
	/// Returns the queue's length
	inline unsigned int numCommands() const { return lastNumCommands_; }

	/// Returns the total number of vertices to be rendered by the queue for a specified command type
	inline unsigned int numVertices(RenderCommand::CommandType type) const { return typedLastNumVertices_[type]; }
	/// Returns the number of commands to render a specified category of commands
	inline unsigned int numCommands(RenderCommand::CommandType type) const { return typedLastNumCommands_[type]; }

  private:
	/// The current sum of vertices for every command in the queue
	unsigned int numVertices_;
	/// The sum of vertices in the previous frame (it never contains a partial sum)
	unsigned int lastNumVertices_;
	/// The sum of draw commands in the previous frame (it never contains a partial sum)
	unsigned int lastNumCommands_;

	/// The current sum of vertices for a specified command type
	StaticArray<unsigned int, RenderCommand::TYPE_COUNT> typedNumVertices_;
	/// The current sum of draw commands for a specified command type
	StaticArray<unsigned int, RenderCommand::TYPE_COUNT> typedNumCommands_;
	/// The sum of vertices for a specified command type in the previous frame (it never contains a partial sum)
	StaticArray<unsigned int, RenderCommand::TYPE_COUNT> typedLastNumVertices_;
	/// The sum of draw commands for a specified command type in the previous frame (it never contains a partial sum)
	StaticArray<unsigned int, RenderCommand::TYPE_COUNT> typedLastNumCommands_;

	/// Array of opaque render command pointers
	Array<RenderCommand *> opaqueRenderCommands_;
	/// Array of transparent render command pointers
	Array<RenderCommand *> transparentRenderCommands_;
};

}

#endif