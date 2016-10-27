#include "SpriteBatch.h"

#include <algorithm>

namespace TimEng{

	Glyph::Glyph(const glm::vec4& destinationRectangle, const glm::vec4& uvRectangle, GLuint Texture, float Depth, const ColorRGBA8& color) :
		texture(Texture),
		depth(Depth){

		topLeft.color = color;
		topLeft.setPosition(destinationRectangle.x, destinationRectangle.y);
		topLeft.setUV(uvRectangle.x, uvRectangle.y);

		topRight.color = color;
		topRight.setPosition(destinationRectangle.x + destinationRectangle.z, destinationRectangle.y);
		topRight.setUV(uvRectangle.x + uvRectangle.z, uvRectangle.y);

		bottomLeft.color = color;
		bottomLeft.setPosition(destinationRectangle.x, destinationRectangle.y + destinationRectangle.w);
		bottomLeft.setUV(uvRectangle.x, uvRectangle.y + uvRectangle.w);

		bottomRight.color = color;
		bottomRight.setPosition(destinationRectangle.x + destinationRectangle.z, destinationRectangle.y + destinationRectangle.w);
		bottomRight.setUV(uvRectangle.x + uvRectangle.z, uvRectangle.y + uvRectangle.w);
	}

	Glyph::Glyph(const glm::vec4& destinationRectangle, const glm::vec4& uvRectangle, GLuint Texture, float Depth, const ColorRGBA8& color, float angle) :
		texture(Texture),
		depth(Depth){

		glm::vec2 halfDims(destinationRectangle.z / 2.0f, destinationRectangle.w / 2.0f);

		glm::vec2 tl(-halfDims.x, halfDims.y);
		glm::vec2 bl(-halfDims.x, -halfDims.y);
		glm::vec2 br(halfDims.x, -halfDims.y);
		glm::vec2 tr(halfDims.x, halfDims.y);

		tl = rotatePoint(tl, angle) + halfDims;
		bl = rotatePoint(bl, angle) + halfDims;
		tr = rotatePoint(tr, angle) + halfDims;
		br = rotatePoint(br, angle) + halfDims;

		topLeft.color = color;
		topLeft.setPosition(destinationRectangle.x + tl.x, destinationRectangle.y + tl.y);
		topLeft.setUV(uvRectangle.x, uvRectangle.y);

		topRight.color = color;
		topRight.setPosition(destinationRectangle.x + tr.x, destinationRectangle.y + tr.y);
		topRight.setUV(uvRectangle.x + uvRectangle.z, uvRectangle.y);

		bottomLeft.color = color;
		bottomLeft.setPosition(destinationRectangle.x + bl.x, destinationRectangle.y + bl.y);
		bottomLeft.setUV(uvRectangle.x, uvRectangle.y + uvRectangle.w);

		bottomRight.color = color;
		bottomRight.setPosition(destinationRectangle.x + br.x, destinationRectangle.y + br.y);
		bottomRight.setUV(uvRectangle.x + uvRectangle.z, uvRectangle.y + uvRectangle.w);
	}
	glm::vec2 Glyph::rotatePoint(glm::vec2 pos, float angle){
		glm::vec2 newv;

		newv.x = pos.x * cos(angle) - pos.y * sin(angle);
		newv.y = pos.x * sin(angle) + pos.y * cos(angle);

		return newv;
	}



	SpriteBatch::SpriteBatch()
	{
	}


	SpriteBatch::~SpriteBatch()
	{
	}

	void SpriteBatch::init(){
		createVertexArray();
	}

	void SpriteBatch::begin(GlyphSortType sortType /* GlyphSortType::TEXTURE */){
		_sortType = sortType;
		_renderBatches.clear();

		_glyphs.clear();
	}

	void SpriteBatch::end(){
		_glyphPointers.resize(_glyphs.size());
		for (int i = 0; i < _glyphPointers.size(); i++){
			_glyphPointers[i] = &_glyphs[i];
		}
		sortGlyphs();
		createRenderBatches();
	}

	void SpriteBatch::draw(	const glm::vec4& destinationRectangle, const glm::vec4& uvRectangle, 
							GLuint texture, float depth, const ColorRGBA8& color){
		_glyphs.emplace_back(destinationRectangle, uvRectangle, texture, depth, color);
	}

	void SpriteBatch::draw(	const glm::vec4& destinationRectangle, const glm::vec4& uvRectangle,
							GLuint texture, float depth, const ColorRGBA8& color, float angle){
		_glyphs.emplace_back(destinationRectangle, uvRectangle, texture, depth, color, angle);

	}

	void SpriteBatch::draw(	const glm::vec4& destinationRectangle, const glm::vec4& uvRectangle,
							GLuint texture, float depth, const ColorRGBA8& color, const glm::vec2& dir){
		const glm::vec2 right(1.0f, 0.0f);

		float angle = acos(glm::dot(right, dir));
		if (dir.y < 0){
			angle = -angle;
		}

		_glyphs.emplace_back(destinationRectangle, uvRectangle, texture, depth, color, angle);

	}

	void SpriteBatch::renderBatch(){
		glBindVertexArray(_vao);

		for (int i = 0; i < _renderBatches.size(); i++){
			glBindTexture(GL_TEXTURE_2D, _renderBatches[i].texture);
			glDrawArrays(GL_TRIANGLES, _renderBatches[i].offset, _renderBatches[i].numVerticies);
		}

		glBindVertexArray(0);
	}

	void SpriteBatch::createRenderBatches(){
		std::vector<Vertex> verticies;
		verticies.resize(_glyphPointers.size() * 6);

		if (_glyphPointers.empty()){
			return;
		}
		int offset = 0;
		int currentvertex = 0;

		_renderBatches.emplace_back(offset, 6, _glyphPointers[0]->texture);

		verticies[currentvertex++] = _glyphPointers[0]->topLeft;
		verticies[currentvertex++] = _glyphPointers[0]->bottomLeft;
		verticies[currentvertex++] = _glyphPointers[0]->bottomRight;
		verticies[currentvertex++] = _glyphPointers[0]->bottomRight;
		verticies[currentvertex++] = _glyphPointers[0]->topRight;
		verticies[currentvertex++] = _glyphPointers[0]->topLeft;
		offset += 6;

		for (int currentglyph = 1; currentglyph < _glyphPointers.size(); currentglyph++){
			if (_glyphPointers[currentglyph]->texture != _glyphPointers[currentglyph - 1]->texture){
				_renderBatches.emplace_back(offset, 6, _glyphPointers[currentglyph]->texture);
			}
			else{
				_renderBatches.back().numVerticies += 6;
			}

			verticies[currentvertex++] = _glyphPointers[currentglyph]->topLeft;
			verticies[currentvertex++] = _glyphPointers[currentglyph]->bottomLeft;
			verticies[currentvertex++] = _glyphPointers[currentglyph]->bottomRight;
			verticies[currentvertex++] = _glyphPointers[currentglyph]->bottomRight;
			verticies[currentvertex++] = _glyphPointers[currentglyph]->topRight;
			verticies[currentvertex++] = _glyphPointers[currentglyph]->topLeft;

			offset += 6;
		}

		glBindBuffer(GL_ARRAY_BUFFER, _vbo);
		//orphan the buffer
		glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(Vertex), nullptr, GL_DYNAMIC_DRAW);
		//upload the buffer
		glBufferSubData(GL_ARRAY_BUFFER, 0, verticies.size() * sizeof(Vertex), verticies.data());

		glBindBuffer(GL_ARRAY_BUFFER, 0);

	}

	void SpriteBatch::createVertexArray(){

		if (_vao == 0){
			glGenVertexArrays(1, &_vao);
		}
		glBindVertexArray(_vao);


		if (_vbo == 0){
			glGenBuffers(1, &_vbo);
		}
		glBindBuffer(GL_ARRAY_BUFFER, _vbo);

		glEnableVertexAttribArray(0);
		glEnableVertexAttribArray(1);
		glEnableVertexAttribArray(2);

		//This is the position attribute pointer
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, position));

		//This is the color attribute pointer
		glVertexAttribPointer(1, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (void*)offsetof(Vertex, color));

		//This is the UV attribute pointer
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, uv));

		glBindVertexArray(0);
	}

	void SpriteBatch::sortGlyphs(){
		switch (_sortType){
		case GlyphSortType::BACK_TO_FRONT:
			std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareBackToFront);
			break;
		case GlyphSortType::FRONT_TO_BACK:
			std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareFrontToBack);
			break;
		case GlyphSortType::TEXTURE:
			std::stable_sort(_glyphPointers.begin(), _glyphPointers.end(), compareTexture);
			break;

		}
	}

	bool SpriteBatch::compareFrontToBack(Glyph* a, Glyph* b){
		return (a->depth < b->depth);
	}
	bool SpriteBatch::compareBackToFront(Glyph* a, Glyph* b){
		return (a->depth > b->depth);
	}
	bool SpriteBatch::compareTexture(Glyph* a, Glyph* b){
		return (a->texture > b->texture);
	}

}