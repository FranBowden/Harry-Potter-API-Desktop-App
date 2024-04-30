#pragma once
#include "ofMain.h"
#include "ofxJSON.h" //used for api
#include "ofxThreadedImageLoader.h" //used to manage item threads
#include <vector>
#include <algorithm>
#include <string>


class ofApp : public ofBaseApp{

	public:
		ofxJSONElement json; //Json object stores data returned from API
		ofxThreadedImageLoader loader; //help load images

		struct Item { //struct to store item data in
			ofRectangle container;
			string name, effect, category, URL_Img;
			ofImage API_Img;
			bool fav;
		};
			
		Item item;
		
		void draw();
		//set up and load UI
		void setup();
		void loadAPIImages();
		void setupImages();
		void setupUIRectangles();

		//page functions
		void beginningPage();
		
		//Display functions
		void displayOverlayWindow();
		void displayFavWindow();
		void displayItems();
		void displayMenu();


		void getItem(vector<Item> &items);
		void filterItems(vector<Item>& item);
		bool validKey(int key);//will check if valid key can be added to string
		
		//interactive functions:
		void keyPressed(int key);
		void mousePressed(int x, int y, int button);
		
		//function returns a wrapped string to keep text on screen
		string wrapString(string text, int width);

		enum class States { //Handle app state
			MENU,
			SPELLS,
			POTIONS
		};

		States state;
			
		//vectors
		vector<Item> potions; //stores potion api
		vector<Item> spells; //stores spell api
		vector<Item*> displayedItems; //pointer to display items
		
		//UI 
		ofRectangle book, favTabBTN, menuBTN, infoWindow, infoTextbox, gutter, searchBar;
		ofTrueTypeFont headerFont, mainFont;
		ofImage potionBTN, spellBTN, exitBTN, favBTN, homeBTN, unFillFavBTN, favTabIcon, turnLeft, turnRight;

		//variables:
		string word, api;
		
		int page, endOfPages, start, end, remainer, itemsPrinted, idOverlay, pageNumLeft, pageNumRight;
		int xPotion, yPotion, wPotion, hPotion;
		int xSpell, ySpell, wSpell, hSpell;

		bool textInput, loadedALLImgs, isOverlay,  leftBTN, rightBTN, isFavouriteDisplay;
};