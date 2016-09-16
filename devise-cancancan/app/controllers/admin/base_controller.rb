class Admin::BaseController < ApplicationController
	before_filter :authenticate_admin_user!
	alias :current_user :current_admin_user

  def index
  end
end
