#include "ofApp.h"

//-------------------------------------------------------------
void ofApp::setup() {
	state = States::MENU; //sets state to potion
	loadAPIImages(); //load all images from api
	setupImages(); //load the images in the bin data folder

	ofSetWindowTitle("Wizard Handy Guide"); //application title

	//load fonts
	headerFont.load("HarryPotter.ttf", 15);
	mainFont.load("MagicOwl.otf", 30);
	
	setupUIRectangles(); //setup rectangles for UI

	//set bools to false:
	isOverlay = false; 
	isFavouriteDisplay = false;
	leftBTN = false; 
	rightBTN = false;
	textInput = false;

	wPotion = 400;
	hPotion = 400;
	yPotion = 200;
	xPotion = 200;

	wSpell = 400;
	hSpell = 400;
	ySpell = 200;
	xSpell = 700;	
	
	word = "";//set word to empty on start up

	beginningPage(); //function to reset the book pages
}

void ofApp::beginningPage() {
	page = 1; //set page to 1
	pageNumLeft = 1;
	pageNumRight = pageNumLeft + 1;
	start = 0;
	end = 8;
}

void ofApp::setupImages() {
	//loading in all images from bin folder and resizing 
	potionBTN.load("potionBTN.png");
	spellBTN.load("SpellBTN.png");

	exitBTN.load("exitBtn.png");
	exitBTN.resize(50, 50);

	favBTN.load("filledHeart.png");
	favBTN.resize(30, 30);

	unFillFavBTN.load("heartBTN.png");
	unFillFavBTN.resize(30, 30);

	favTabIcon.load("filledHeartTabIcon.png");
	favTabIcon.resize(35, 35);

	homeBTN.load("home.png");
	homeBTN.resize(35, 35);

	turnLeft.load("turnLeft.png");
	turnLeft.resize(100, 100);

	turnRight.load("turnRight.png");
	turnRight.resize(100, 100);
}

void ofApp::setupUIRectangles() {
	//setting the x,y, width and height of each rectangle:
	favTabBTN.set((ofGetWidth() / 2) + 250, 40, 80, 80);
	menuBTN.set((ofGetWidth() / 2) + 380, 40, 80, 80);

	book.set(50, 100, ofGetWidth() - 100, ofGetHeight() - 110);

	gutter.set(ofGetWidth() / 2 - 2, 0, 2, ofGetHeight());

	searchBar.set(50, 40, 300, 50);

	infoWindow.set(ofGetWidth() / 2 - 300, ofGetHeight() / 2 - 225, 600, 450);

	infoTextbox.set((ofGetWidth() / 2) + 10, (ofGetHeight() / 2) - 130, 250, 280);
}


void ofApp::loadAPIImages() {

	api = "https://api.potterdb.com/v1/potions"; //api link for potions
	getItem(potions); //store the items from that api into potions vector

	api = "https://api.potterdb.com/v1/spells"; //api link fpr spells
	getItem(spells); //stores the items from api to spells vector

	for (auto& i : potions) {
		loader.loadFromURL(i.API_Img, i.URL_Img); //load all the images in the vector
	}
	for (auto& i : spells) {
		loader.loadFromURL(i.API_Img, i.URL_Img);
	}
}

//--------------------------------------------------------------
void ofApp::draw() {
	if (state == States::MENU) {
		displayMenu(); //display menu
	}
	else {
		//Drawing UI
		ofBackground(32, 21, 64); //set background to purple
		ofSetColor(49, 26, 107);
		ofDrawRectRounded(favTabBTN, 10);
		ofDrawRectRounded(menuBTN, 10);
		ofSetColor(61, 31, 135);
		ofDrawRectRounded(book, 10);
		ofSetColor(32, 21, 64);
		ofDrawRectangle(gutter);
		ofSetColor(255);
	

		homeBTN.draw(menuBTN.getX() + 25, 55);
		favTabIcon.draw(favTabBTN.getX() + 25, 55);
		turnLeft.draw(0, ofGetHeight() - turnLeft.getWidth());
		turnRight.draw(ofGetWidth() - turnRight.getWidth(), ofGetHeight() - turnRight.getWidth());

		//page numbers
		mainFont.load("MagicOwl.otf", 15);
		mainFont.drawString(to_string(pageNumLeft), 17, ofGetHeight() - 12); //page number for left
		mainFont.drawString(to_string(pageNumRight), ofGetWidth() - 30, ofGetHeight() - 12); //page number for right
		
		//filters what is being displayed:
		if (state == States::POTIONS) {
			filterItems(potions);
			if (isFavouriteDisplay == false)
			{
				mainFont.load("MagicOwl.otf", 30);
				mainFont.drawString("Potions!", ofGetWidth() / 2 - mainFont.stringWidth("Potions") / 2, 70);
			}
		}
		else if (state == States::SPELLS) {
			filterItems(spells);
			if (isFavouriteDisplay == false)
			{
				mainFont.load("MagicOwl.otf", 30);
				mainFont.drawString("Spells!", ofGetWidth() / 2 - mainFont.stringWidth("Spells") / 2, 70);
			}
		}                    		
		displayItems(); //then displays the items

		if (isOverlay) { //if overlay is true then
			displayOverlayWindow();
		}

		if (!textInput) {//if not capturing text input
			ofSetColor(200);//set colour to grey for text box
		}
		else {
			ofSetColor(255); //set color to white for text box
		}

		ofDrawRectRounded(searchBar, 10);//draw rectangle using textBox values
		ofSetColor(0);//set colour to black for text
		mainFont.load("MagicOwl.otf", 20);
		mainFont.drawString(word, 80, 75);//drawing text to the screen*/
	}
}

void ofApp::displayMenu() {
		isFavouriteDisplay = false;
		ofBackground(24, 12, 55);
		ofSetColor(255);
		mainFont.drawString("Please select either potions or spells!", ofGetWidth()/2 - mainFont.stringWidth("Please select either potions or spells!")/2, 100); //title for menu

		//*two image btns*/
		potionBTN.resize(wPotion, hPotion);
		spellBTN.resize(wSpell, hSpell);
		potionBTN.draw(xPotion, yPotion);
		spellBTN.draw(xSpell, ySpell);
}
	
void ofApp::displayFavWindow() {
	
	mainFont.load("MagicOwl.otf", 30);
	mainFont.drawString("Favourites!", ofGetWidth() / 2 - mainFont.stringWidth("Favourites") / 2, 70); //fav title
	
	displayedItems.erase(remove_if(displayedItems.begin(), displayedItems.end(),[](Item* item) { 
		return !item->fav;  //remove item from displayItems if item is not equal to favourite being true
		}),displayedItems.end()); //only keep the items that are true in the vector
	
	//update page information
	page = 1;
	pageNumLeft = 1;
	pageNumRight = pageNumLeft + 1;
	start = 0;
	end = displayedItems.size(); //need size, not 8 otherwise vector error
}

void ofApp::filterItems(vector<Item>& item) {
	
	//update item vector
		if (word.length() > 0) {
			displayedItems.clear(); //clear items
			for (auto& i : item) {
				transform(i.name.begin(), i.name.end(), i.name.begin(), ::tolower); 
				transform(word.begin(), word.end(), word.begin(), ::tolower);

				if (word.compare(0, word.length(), i.name.substr(0, word.length())) == 0) {
					displayedItems.push_back(&i); //push back matched items
				}
			}
		}
		else if (isFavouriteDisplay) {
			displayFavWindow(); //if favourite is true then display the favourite window
		
		}
		else {
			displayedItems.clear();
			for (auto& i : item) {
				displayedItems.push_back(&i); //otherwise display every item
			}
		}
	
	int size = displayedItems.size();

	if (textInput) {
		start = 0;
		end = size;
	}
	if (size < 8) {
		endOfPages = 1;
	}
	else {
		endOfPages = size / 8; //calculate amount of pages 
		remainer = size % 8; //calculate remainer
	}
}

void ofApp::displayItems() {

	int yPos = 150;
	int width = 220;
	int xPos = 80;
	int height = 220;
	itemsPrinted = 0;
	
	if (!displayedItems.empty()) { //if vector is not empty then

	//	cout << " Start: " << start << " " << " End: " << end << endl;
		for (int i = start; i < end; i++) { //start loop 

			if (itemsPrinted < 8) { //only display the first 8 items
				ofSetColor(38, 14, 94);
				displayedItems[i]->container.set(xPos - 5, yPos - 5, 230, 230);
				ofDrawRectRounded(displayedItems[i]->container, 10); //drawing container
				ofSetColor(255);

				//ratio of image and fixing height and width:
				height = displayedItems[i]->API_Img.getHeight() * (width / displayedItems[i]->API_Img.getWidth()); 
				if (height > 200) {
					displayedItems[i]->API_Img.resize(width, height);
					displayedItems[i]->API_Img.crop(0, 0, width, 200);
				}

				displayedItems[i]->API_Img.draw(xPos, yPos, width, height); //draws the image


				mainFont.load("MagicOwl.otf", 15); 
				mainFont.drawString(displayedItems[i]->name, xPos + (110 - (mainFont.stringWidth(displayedItems[i]->name) / 2)), yPos + 215); //draw name of item

				xPos += 300; //move the next image along xPos

				itemsPrinted++; //add one to itemsPrinted

				if (itemsPrinted % 4 == 0) {  //move to next row after 4 prints
					xPos = 80; //reset xPos
					yPos += 270; //lower image
				}
			}
		}
	}
}

void ofApp::displayOverlayWindow() {
	//UI Display:
		ofSetColor(32, 21, 64);
		ofDrawRectRounded(infoWindow, 10); 

		ofSetColor(61, 31, 135);
		ofDrawRectRounded(infoTextbox, 10);
		
		ofSetColor(255);

		exitBTN.draw(((ofGetWidth() / 2) - 335) + infoWindow.getWidth(), infoWindow.getTop() - 20); //exit btn

		//favourite btns
		if (displayedItems[idOverlay]->fav == false) {
			unFillFavBTN.draw(infoTextbox.getX() + infoTextbox.getWidth() - 40, infoTextbox.getY() + 10); //display unfilled btn
			
		}
		else if (displayedItems[idOverlay]->fav == true) {
			favBTN.draw(infoTextbox.getX() + infoTextbox.getWidth() - 40, infoTextbox.getY() + 10); //display filled
			
		}
		
		displayedItems[idOverlay]->API_Img.draw((ofGetWidth() - 500) / 2, (ofGetHeight() - 230) / 2, 230, 230); //draws the image 

		headerFont.load("HarryPotter.ttf", 30);
		headerFont.drawString(displayedItems[idOverlay]->name, (ofGetWidth() - headerFont.stringWidth(displayedItems[idOverlay]->name)) / 2, infoWindow.getTop() + 80); //title
		mainFont.load("MagicOwl.otf", 15);
		mainFont.drawString(wrapString("Effects:\n" + displayedItems[idOverlay]->effect + "\n\nCategory: \n" + displayedItems[idOverlay]->category, 300), ofGetWidth() / 2 + 25, ofGetHeight() / 2 - 50); //draws the text that gives the information
}


void ofApp::getItem(vector<Item> &items) {
	items.clear();
	json.open(api); //open api 
	cout << api << endl;
	if (!json.open(api)) { //if it doesnt open then
		// error handling for failed JSON 
		cout << "JSON Error from API: " << api << endl;
		return;
	}

	//cout << "API Response: " << json.getRawString() << endl;

	for (auto& itemData : json["data"]) {
		string img = itemData["attributes"]["image"].asString(); //image
		if (!img.empty()) {
		
			item.URL_Img = img;
			item.name = itemData["attributes"]["name"].asString(); //gets the name
			item.effect = itemData["attributes"]["effect"].asString(); //gets the effect
			item.category = itemData["attributes"]["category"].asString(); //gets the category
			item.fav = false; 
			items.push_back(item); //push back into vector
		}
	}
}


//--------------------------------------------------------------
void ofApp::keyPressed(int key) {
	if ((state == States::POTIONS || state == States::SPELLS) && !isOverlay) {
		if (!textInput) {


			//buttons to switch pages:
			if (key == OF_KEY_LEFT && page > 1) {

				start -= 8;
				end -= (page == endOfPages) ? remainer : 8;

				page--; //minus page
				pageNumRight = pageNumLeft;
				pageNumLeft--;
			}
			if (key == OF_KEY_RIGHT && page < endOfPages) {
				page++;

				pageNumLeft = pageNumRight;
				pageNumRight++;

				start += 8;
				end += (page == endOfPages) ? remainer : 8;
			}
		}


		if (validKey(key)) {//if text box is selected and valid key entered
			if ((key == OF_KEY_BACKSPACE || key == OF_KEY_DEL)) {//check if key is delete
				if (word.length() != 0) {//if word has letters
					word.pop_back();//remove letter at end
				}


			}
			else {//otherwise accept the key
				if (word.length() < 30) {//check string is less than 20 chars
					ofUTF8Append(word, key);//add key to word string
					cout << word << endl;
				}
			}
		}

	}
}


bool ofApp::validKey(int key) {
	return (key == OF_KEY_ALT || key == OF_KEY_CONTROL || key == OF_KEY_SHIFT || key == OF_KEY_COMMAND || key == OF_KEY_LEFT_SHIFT || key == OF_KEY_RIGHT_SHIFT || key == OF_KEY_LEFT || key == OF_KEY_RIGHT) ? false : true;
}
//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button) {

	if (state == States::MENU) {
		ofRectangle potionBTNRect(xPotion, yPotion, wPotion, hPotion);
		ofRectangle spellBTNRect(xSpell, ySpell, wSpell, hSpell);

		if (potionBTNRect.inside(x, y)) {
			cout << "Clicked on POTION btn" << endl;
			isFavouriteDisplay = false;
			beginningPage();
			state = States::POTIONS; //if mouse presses potion set state to potion
		}
		else if (spellBTNRect.inside(x, y)) {
			cout << "Clicked on SPELL btn" << endl; //if clicked on spell set state to spell
			isFavouriteDisplay = false;
			beginningPage();
			state = States::SPELLS;
		}
	}

	else if ((state == States::POTIONS || state == States::SPELLS) && !isOverlay) {
		if (!displayedItems.empty() && !isOverlay) {

			for (int i = start; i < end; i++) {
				if (displayedItems[i]->container.inside(x, y)) { //if item is clicked on
					isOverlay = true;
					idOverlay = i; //id found
					break; //break loop
				};
			}
		}
		

		if (menuBTN.inside(x, y)) { //Home menu btn
			mainFont.load("MagicOwl.otf", 30);
			isFavouriteDisplay = false;
			state = States::MENU;
		}

		if (searchBar.inside(x, y)) {//checks if textbox is selected
			isFavouriteDisplay = false;
			textInput = true;//enable text input
			word = ""; //reset worked
		} 
		else {
			textInput = false;
		}

		if (favTabBTN.inside(x, y)) { //if favourite tab is clicked on
			cout << "favourite tab button clicked" << endl;
			word = ""; //reset word
			isFavouriteDisplay = true; //display is true
		}

		//left button
		if ((x >= 0 && x <= 0 + turnLeft.getWidth()) &&
			(y >= ofGetHeight() - turnLeft.getWidth() && y <= ofGetHeight() - turnLeft.getHeight() + turnLeft.getHeight())) {
			cout << "left image clicked" << endl;
			leftBTN = true;
		}

		//right button
		if ((x >= ofGetWidth() - turnRight.getWidth() && x <= ofGetWidth() - turnRight.getWidth() + turnLeft.getWidth()) &&
			(y >= ofGetHeight() - turnRight.getHeight() && y <= ofGetHeight() - turnRight.getHeight() + turnRight.getHeight())) {
			cout << "right image clicked" << endl;
			rightBTN = true;
		}

		if (leftBTN && page > 1) {
			//managing previous page
			start -= 8;
			end -= (page == endOfPages) ? remainer : 8;

			page--;
			pageNumRight = pageNumLeft;
			pageNumLeft--;
			leftBTN = false;

		}
		if (rightBTN && page < endOfPages) {
			//managing next page:
			page++;
			pageNumLeft = pageNumRight;
			pageNumRight++;
			start += 8;
			end += (page == endOfPages) ? remainer : 8;

			rightBTN = false;

		}

	}
	if (isOverlay) { //if overlay is true
		textInput = false;
		//if favourite btn is pressed:
		if ((x >= (infoTextbox.getX() + infoTextbox.getWidth() - 40 && x <= infoTextbox.getX() + infoTextbox.getWidth() - 40 + unFillFavBTN.getWidth()) &&
			(y >= infoTextbox.getY() + 10 && y <= infoTextbox.getY() + 10 + unFillFavBTN.getHeight()))) {
			
			if (isFavouriteDisplay) { 
				auto& it = displayedItems.begin() + idOverlay;
				int index = distance(displayedItems.begin(), it);  //gets the new modified index
				displayedItems[index]->fav = false; //make it false 
				displayedItems.erase(it);
				isOverlay = false; //set to false 
			}
			else if (!isFavouriteDisplay) {
				if (displayedItems[idOverlay]->fav == false) {
					displayedItems[idOverlay]->fav = true;
				}
				else if (displayedItems[idOverlay]->fav == true) {
					displayedItems[idOverlay]->fav = false;
				}
			}
		}
	
		//exit button
		if ((x >= ((ofGetWidth() / 2) - 335) + infoWindow.getWidth() && x <= ((ofGetWidth() / 2) - 335) + infoWindow.getWidth() + exitBTN.getWidth()) &&
			(y >= infoWindow.getTop() - 20 && y <= infoWindow.getTop() - 20 + exitBTN.getHeight())) {
			isOverlay = false;
		}


	}

	
	
}


//function adds line breaks into string passed to it and returns formatted string
string ofApp::wrapString(string text, int width) {
	string typeWrapped = "";
	string tempString = "";
	vector <string> words = ofSplitString(text, " "); //create vector full of individual words in string passed in

	for (int i = 0; i < words.size(); i++) { //run through vector
		string wrd = words[i]; //get current word in vector

		// if we aren't on the first word, add a space
		if (i > 0) {
			tempString += " ";
		}
		tempString += wrd; //add current word to temp string

		int stringwidth = headerFont.stringWidth(tempString); //set string width to length of line

		if (stringwidth >= width) {//check string with to add either space or new line before current word
			typeWrapped += "\n"; //if line is now longer than desired width add a new line
			tempString = wrd; // make sure we're including the extra word on the next line
		}
		else if (i > 0) {
			typeWrapped += " "; // if we aren't on the first word, add a space
		}
		typeWrapped += wrd; //add current word to string to be returned with new lines for wrapping
	}

	return typeWrapped;

}