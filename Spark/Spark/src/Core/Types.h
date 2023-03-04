	struct Color {
	public:
		float red, green, blue, alpha;
		Color() {

		}
		Color(float v1, float v2, float v3, float v4) : red(v1), green(v2), blue(v3), alpha(v4) {

		}
		glm::vec4 toVec4() {
			return glm::vec4(red, green, blue, alpha);
		}
		static Color get255Color(float v1, float v2, float v3, float v4) {
			return Color((int)v1 * 255, (int)v2 * 255, (int)v3 * 255, (int)v4 * 255);
		}
		static Color get1Color(float v1, float v2, float v3, float v4) {
			return Color((float)v1 / 255.0f, (float)v2 / 255.0f, (float)v3 / 255.0f, (float)v4 / 255.0f);
		}

	};