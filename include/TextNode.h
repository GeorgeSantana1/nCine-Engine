#ifndef CLASS_NCINE_TEXTNODE
#define CLASS_NCINE_TEXTNODE

#include "DrawableNode.h"
#include "Font.h"
#include "Color.h"
#include "Array.h"
#include "ncString.h"

namespace ncine {

class FontGlyph;

/// A scene node to draw a text label
class DLL_PUBLIC TextNode : public DrawableNode
{
  public:
	/// Default maximum length for a string to be rendered
	/*! This number affects the size of both the string container and the VBO. */
	static const unsigned int DefaultStringLength = 256;

	/// Horizontal alignment modes
	enum Alignment
	{
		ALIGN_LEFT,
		ALIGN_CENTER,
		ALIGN_RIGHT
	};

	TextNode(SceneNode *parent, Font *font, unsigned int maxStringLength);
	TextNode(SceneNode *parent, Font *font);

	/// Returns the width of rendered text
	virtual float width() const;
	/// Returns the height of rendered text
	virtual float height() const;
	/// Returns the absolute width of rendered text
	virtual float absWidth() const;
	/// Returns the absolute height of rendered text
	virtual float absHeight() const;

	/// Returns true if kerning is enabled for this node rendering
	inline bool withKerning() const { return withKerning_; }
	/// Sets the kerning flag for this node rendering
	void enableKerning(bool withKerning);
	/// Gets the horizontal text alignment
	inline Alignment alignment() const { return alignment_; }
	/// Sets the horizontal text alignment
	void setAlignment(Alignment alignment);

	/// Gets the font base scaled by the scale factor
	inline float fontBase() const { return font_->base() * scaleFactor_; }
	/// Gets the font line height scaled by the scale factor
	inline float fontLineHeight() const { return font_->lineHeight() * scaleFactor_; }
	/// Sets the string to render
	void setString(const String &string);

	virtual void draw(RenderQueue &renderQueue);

	inline static ObjectType sType() { return TEXTNODE_TYPE; }

  private:
	/// The string to be rendered
	String string_;
	/// Dirty flag for vertices and texture coordinates
	bool dirtyDraw_;
	/// Dirty flag for boundary rectangle
	mutable bool dirtyBoundaries_;
	/// Kerning flag for rendering
	bool withKerning_;
	/// The font class used to render text
	Font *font_;
	/// The array of vertex positions interleaved with texture coordinates for every glyph in the batch
	Array<float> interleavedVertices_;

	/// Advance on the X-axis for the next processed glyph
	mutable float xAdvance_;
	/// Total advance on the X-axis for the longest line (horizontal boundary)
	mutable float xAdvanceSum_;
	/// Advance on the Y-axis for the next processed glyph
	mutable float yAdvance_;
	/// Total advance on the Y-axis for the entire string (vertical boundary)
	mutable float yAdvanceSum_;
	/// Text width for each line of text
	mutable Array<float> lineLengths_;
	/// Horizontal text alignment
	Alignment alignment_;

	/// Initializes the object with the parameters passed to the constructor
	void init(unsigned int maxStringLength);
	/// Calculates rectangle boundaries for the rendered text
	void calculateBoundaries() const;
	/// Calculates align offset for a particular line
	float calculateAlignment(unsigned int lineIndex) const;
	/// Fills the batch draw command with data from a glyph
	void processGlyph(const FontGlyph *glyph);

	virtual void updateRenderCommand();
};

}

#endif
