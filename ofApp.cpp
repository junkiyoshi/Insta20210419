#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(1.2);
	ofSetRectMode(ofRectMode::OF_RECTMODE_CENTER);
	
	this->mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();

	int len = 20;
	auto threshold = len * sqrt(2);

	for (int base_x = -220; base_x <= 220; base_x += 220) {

		for (int base_y = -220; base_y <= 220; base_y += 220) {

			vector<glm::vec3> vertices;
			for (int x = -100; x <= 100; x += len) {

				for (int y = -100; y <= 100; y += len) {

					auto noise_value = ofNoise((base_x + x) * 0.008, (base_y + y) * 0.008, ofGetFrameNum() * 0.005);

					if (noise_value > 0.55) {

						vertices.push_back(glm::vec3(x + base_x, base_y + y, 0));
					}
				}
			}

			for (int i = 0; i < vertices.size(); i++) {

				int index = -1;
				for (int k = i + 1; k < vertices.size(); k++) {

					if (glm::distance(vertices[i], vertices[k]) <= threshold) {

						if (index < 0) {

							this->mesh.addVertex(vertices[i]);
							index = this->mesh.getNumVertices() - 1;
						}
						this->mesh.addVertex(vertices[k]);

						this->mesh.addIndex(index);
						this->mesh.addIndex(this->mesh.getNumVertices() - 1);
					}
				}
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	ofNoFill();
	for (int base_x = -220; base_x <= 220; base_x += 220) {

		for (int base_y = -220; base_y <= 220; base_y += 220) {
	
			ofDrawRectangle(base_x, base_y, 200, 200);
		}
	}

	this->mesh.drawWireframe();

	ofFill();
	for (auto& vertex : this->mesh.getVertices()) {

		ofDrawCircle(vertex, 3);
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}