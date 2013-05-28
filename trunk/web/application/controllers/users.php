<?php

class Users extends MY_Controller {

    public function __construct() {
        parent::__construct();
        $this->layout = 'layouts/master';
        $this->load->library('login');
    }

    public function index() {
        $data['title'] = "User List";
        $data['content'] = 'users/index';
        $data['login'] = $this->get_login_info();
        $this->load->view($this->layout, $data);
    }

    public function show($user_id = 1) {
        
        $data['content'] = 'contents/user';
        $data['user'] = $this->get_login_info();
        $data['title'] = $data['user']['name'];
        
        if ($user_id == $this->login->get_id()) {
            $data['is_valid_access'] = 1;
        }
        else {
            $data['is_valid_access'] = 0;            
        }
        
        $this->load->view($this->layout, $data);
    }

    public function groups($user_id = 1) {
        $data['title'] = 'User ' . $user_id;
        $data['content'] = 'users/' . $user_id;
        $data['login'] = $this->get_login_info();        
        $this->load->view($this->layout, $data);
    }

    public function topics($user_id = 1) {
        $data['title'] = 'User Topic Lists' . $user_id;
        $data['content'] = 'users/topics';
        $data['login'] = $this->get_login_info();
        $this->load->view($this->layout, $data);
    }

}