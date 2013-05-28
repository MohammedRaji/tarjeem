<?php

class User extends MY_Model {
    
    public function __construct() {
        parent::__construct();
        $this->table = 'users';
        $this->primary_key_id = 'id';        
    }    
    
}