uniform mat4 projection;

struct TextnodeInstance
{
	mat4 modelView;
	vec4 color;
};

layout (std140) uniform InstancesBlock
{
#ifdef WITH_FIXED_BATCH_SIZE
	TextnodeInstance[BATCH_SIZE] instances;
#else
	TextnodeInstance[819] instances;
#endif
} block;

in vec2 aPosition;
in vec2 aTexCoords;
in uint aMeshIndex;
out vec2 vTexCoords;
out vec4 vColor;

#define i block.instances[aMeshIndex]

void main()
{
	gl_Position = projection * i.modelView * vec4(aPosition, 0.0, 1.0);
	vTexCoords = aTexCoords;
	vColor = i.color;
}
