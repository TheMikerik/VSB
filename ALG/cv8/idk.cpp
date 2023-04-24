 void CreateLeafs(Item currentItem, int intree){

        if (currentItem.key > intree ){         // vetsi
            if (this->higher == NULL){
                Tree* higher_child = new Tree( currentItem );
                this->higher = higher_child;
            }
            else {
                intree = this->higher->item.key;
                this->higher->CreateLeafs(currentItem, intree);
            }
        }
        else if( currentItem.key < intree ){    // mensi
            if (this->lower == NULL){
                Tree* lower_child = new Tree( currentItem );
                this->lower = lower_child;
            }
            else {
                intree = this->lower->item.key;
                this->lower->CreateLeafs(currentItem, intree);
            }
        }
    }