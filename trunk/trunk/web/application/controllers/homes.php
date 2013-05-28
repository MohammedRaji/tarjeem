<?php

class Homes extends MY_Controller {

    public function __construct() {
        parent::__construct();
        $this->load->library('login');
    }

    public function index() {
        $data['title'] = "Home";
        $data['content'] = 'contents/home';
        $data['user'] = $this->get_login_info();
        $this->load->view($this->layout, $data);
    }
    
}