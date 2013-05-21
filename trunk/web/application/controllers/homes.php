<?php

class Homes extends MY_Controller {

    public function __construct() {
        parent::__construct();
        $this->load->library('login');
    }

    public function index() {
        $data['title'] = "Home";
        $data['content'] = 'layouts/home';
        $data['login'] = $this->set_login_status();
        $this->load->view($this->layout, $data);
    }
    
}