<?php

class Homes extends MY_Controller {

    public function __construct() {
        parent::__construct();
        $this->load->library('login');
    }

    public function index() {
        $data['title'] = "Home";
        $data['content'] = 'home/index';
        $data['login'] = $this->set_login_status();
        $this->load->view($this->layout, $data);
    }

    public function login() {
        $data['title'] = "Login";
        $data['content'] = 'home/login';
        $data['login'] = $this->set_login_status();
        $this->load->view($this->layout, $data);
    }    

    public function signup() {
        $data['title'] = "Sign Up";
        $data['content'] = 'home/signup';
        $data['login'] = $this->set_login_status();
        $this->load->view($this->layout, $data);
    }    

    public function about() {
        $data['title'] = "About";
        $data['content'] = 'home/about';
        $data['login'] = $this->set_login_status();
        $this->load->view($this->layout, $data);
    }    
    
}