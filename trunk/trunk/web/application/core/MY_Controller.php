<?php

class MY_Controller extends CI_Controller {

    public $layout;

    public function __construct() {
        parent::__construct();
        $this->load->library('login');
        $this->load->helper('url');        
        $this->layout = 'layouts/master';        
    }
    
    public function set_login_status()
    {
        if ($this->login->validate_session()) {
            $data['is_logged'] = 1;
        } else {
            $data['is_logged'] = 0;
        }        
        
        return $data;        
    }

}